#ifndef _Performance_H
#define _Performance_H

#include "CH.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <math.h> 

#include <vector>

#include <sys/ioctl.h>
#include <linux/perf_event.h>
#include <asm/unistd.h>


struct e {
	long long type, config;
	e() {
		type = 0;
		config = 0;
	};

	e(long long init_type, long long init_config) {
		type = init_type;
		config = init_config;
	};
};
typedef std::vector<CH*> CHs;

class Performance {
private:
	CHs ch;
	int perf_size;
	int events;
	int fd;
	e *order;
	int sampleSize;
	
	void _add(perf_type_id type, long long config);
	long long _get(perf_type_id type, long long config);


public:
	void run(std::vector<std::string> files);
	Performance(CHs ch) {
		this->perf_size = 1;
		this->events = 0;
		this->fd = -1;
		this->ch = ch;
		this->order = new e[perf_size];

		// This reports the CPU clock, a high-resolution per-CPU timer.
		// [https://lkml.org/lkml/2009/7/1/198] states it is nanoseconds.
		_add(PERF_TYPE_SOFTWARE, PERF_COUNT_SW_CPU_CLOCK);
	}
	
	~Performance(){
		delete[] order;
	}
};



#endif //_Performance_H
