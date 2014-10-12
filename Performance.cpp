#include "Performance.h"
#include "INC_CH.h"
#include "DC_CH.h"
#include "MbC_CH.h"
#include "MbC2_CH.h"
#include <string>

static long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags) {
	int ret;

	ret = syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags);

	return ret;
}


void Performance::_add(perf_type_id type, long long config){
	struct perf_event_attr pe;
	memset(&pe, 0, sizeof(struct perf_event_attr));
	pe.size = sizeof(struct perf_event_attr);
	pe.exclude_kernel = 1;
	pe.exclude_hv = 1;

	pe.type = type;
	pe.config = config;


	order[events].type = type;
	order[events].config = config;
	events++;

	if (fd == -1){
		/* if changed: change calculations in get */
		pe.read_format = PERF_FORMAT_GROUP; 
		pe.disabled = 1;

		fd = perf_event_open(&pe, 0, -1, -1, 0);
		if (fd < 0) {
			fprintf(stderr, "Error opening leader for %llx / %llx\n", (long long) type, config);
			exit(EXIT_FAILURE);
		}
	}else{
		int ret = perf_event_open(&pe, 0, -1, fd, 0);
		if (ret < 0) {
			fprintf(stderr, "Error connecting to leader for %llx / %llx\n", (long long) type, config);
			exit(EXIT_FAILURE);
		}
	}
}

long long Performance::_get(perf_type_id type, long long config){
	long long buffer[1 /* <nr> */ + (1 /* <value> */ * perf_size /* [nr] */)];
	int readSize = (1 + (1 * perf_size)) * sizeof(long long);
	int r = read(fd, &buffer, readSize);
	if(r == -1) {
		fprintf(stderr, "Error reading from fd\n");
		exit(EXIT_FAILURE);
	}
	for (int index = 0; index < events; index++){
		if(order[index].config == config && order[index].type == type){
			return buffer[1 + index];
		}
	}
	fprintf(stderr, "Could not find sw config: %llx\n", (long long)config);
	exit(EXIT_FAILURE);
}

void Performance::run(std::vector<std::string> files) {
  	std::deque<point> result;
  	for(auto &file : files) {
		for(auto &current : this->ch) {
			for(int i = 0; i < 2; i++) {
				/* Read the file for every run - in case an algorithm changes points */
				FILE *inputFile = fopen(file.c_str(), "r");
				std::deque<point> points;

				/* Measure IO */
				printf("\t%16llx\t", 0LLU);
				// Reset counters
				ioctl(this->fd, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
				// Start counting
				ioctl(this->fd, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
				// Read file
	
				point tmp;
				int totalNumberOfPoints = 0;
				while(fscanf(inputFile, "%lf %lf", &tmp.x, &tmp.y) != EOF){
				  totalNumberOfPoints++;
				  tmp.label = totalNumberOfPoints;
				  points.push_back(tmp);
				  
				}
				// Stop counting
				ioctl(this->fd, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);	
				long long cpuClock  = _get(PERF_TYPE_SOFTWARE, PERF_COUNT_SW_CPU_CLOCK);
				printf("%10lu\t%10d\t%15llu\t%s\t%s\n", result.size(), totalNumberOfPoints, cpuClock, "IO", file.c_str());


				fclose(inputFile);
				/* The next 5 lines helps clearing the cache before next run */
				long long burnout = 0;
				for(int i = 0; i < 1000000; i++) {
					burnout ^= ((rand() | (rand() & (int)sizeof(rand()))) - (~rand() / ( 1 + (rand() % rand())) << i)) >> totalNumberOfPoints;
				}
				// Print the burnout, such that it does not get optimized away
				printf("\t%16llx\t", burnout);
				// Reset counters
				ioctl(this->fd, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
				// Start counting
				ioctl(this->fd, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
				// Get convex hull
				current->convexHull(points, totalNumberOfPoints, result);
				// Stop counting
				ioctl(this->fd, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);	

				cpuClock  = _get(PERF_TYPE_SOFTWARE, PERF_COUNT_SW_CPU_CLOCK);
				printf("%10lu\t%10d\t%15llu\t%s\t%s\n", result.size(), totalNumberOfPoints, cpuClock, current->getName(), file.c_str());
				result.clear();
			}
		}
	}
}


int main(int argc, const char* argv[]) {
	std::string tmp;
	std::vector<std::string> files;
	std::ifstream infile("perf.cfg");
	while (std::getline(infile, tmp)) {
		files.push_back(tmp);
	}
	CHs ch;
	ch.push_back(new INC_CH());
	ch.push_back(new DC_CH());
	ch.push_back(new MbC_CH());
	ch.push_back(new MbC2_CH());
	
	Performance *pt = new Performance(ch);
	pt->run(files);
}
