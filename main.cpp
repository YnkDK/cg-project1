/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Computational Geometry 
** (Fall 2014) at Aarhus Univerity Denmark. 
**
** main.cpp
** Runs tests (correctness and execution time) for all implementations.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#include "CH.h"
#include "INC_CH.h"
#include "DC_CH.h"
#include "MbC_CH.h"
#include "MbC2_CH.h"

void printOut(FILE *out, std::deque<point> &res){

  	int i;
  	for(i=0;i<(int)res.size();i++)
   		 fprintf(out, "%d\n", res[i].label); 

}

void usage(){
  	std::cout<<"Type ./executable (1:Iterative or 2:Divide and Conquer or 3:Mbc1 or 4:Mbc2) inputfile outputfile"<<std::endl;
}
int main(int argc, const char* argv[]) {
  
	if(argc != 4) {
		usage();
	   	return 1;
	}
	
	std::deque<point> res;
	FILE *inputFile = fopen(argv[2], "r");
	FILE *outputFile = fopen(argv[3], "w");
	
	std::deque<point> points;
	
	point tmp;
	int totalNumberOfPoints = 0;
	while(fscanf(inputFile, "%lf %lf", &tmp.x, &tmp.y) != EOF){
	  	totalNumberOfPoints++;
	  	tmp.label = totalNumberOfPoints;
	  	points.push_back(tmp);
	}
	fclose(inputFile);
	
	/* Incremental */
	
	if(atoi(argv[1]) == 1){
		CH *inc = new INC_CH();
	  	inc->convexHull(points, totalNumberOfPoints, res);
	}
	else if(atoi(argv[1]) == 2) {
	  	/* Divide and conquer */
	  	CH *dc = new DC_CH();
	  	dc->convexHull(points, totalNumberOfPoints, res);
	} else if(atoi(argv[1]) == 3) {
		/* Marriage before conquest */
		CH *MbC = new MbC_CH();
		MbC->convexHull(points, totalNumberOfPoints, res);
	} else if(atoi(argv[1]) == 4){
		/* Marriage before conquest */
		CH *MbC2 = new MbC2_CH();
		MbC2->convexHull(points, totalNumberOfPoints, res);
	} 
	else {
		usage();
		return 1;
	}
	printOut(outputFile, res);
	fclose(outputFile);
	
	return 0;
}
