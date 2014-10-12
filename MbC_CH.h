/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Computational Geometry 
** (Fall 2014) at Aarhus Univerity Denmark. 
**
** MbC_CH.h
** Implementation of marriage-before-conquest convex algorithm.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#ifndef _MbC_CH_H
#define _MbC_CH_H

#include "CH.h"

class MbC_CH : public CH {
private:
	virtual void upperHull(std::deque<point>& points, const unsigned int size, std::deque<point> &result, std::deque<point>& erased);
public:
	const char* getName() {
		return "MbC_CH";
	}	
	virtual void convexHull(std::deque<point>& points, const int numPoints, std::deque<point> &result);
	
	MbC_CH() {
		
	}
};

#endif //_MbC_CH_H
