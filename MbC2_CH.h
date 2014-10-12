/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Computational Geometry 
** (Fall 2014) at Aarhus Univerity Denmark. 
**
** MbC_CH.h
** Implementation of marriage-before-conquest convex algorithm.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#ifndef _MbC2_CH_H
#define _MbC2_CH_H

#include "CH.h"

class MbC2_CH : public CH {
private:
	virtual void upperHull(std::deque<point>& points, const unsigned int size, std::deque<point> &result);
	void prune(std::deque<point>& points, std::deque<point> & lowerHullPoints, std::deque<point> &upperHullPoints);
public:
	const char* getName() {
		return "MbC2_CH";
	}	
	virtual void convexHull(std::deque<point>& points, const int numPoints, std::deque<point> &result);
	
	MbC2_CH() {
		
	}
};

#endif //_MbC2_CH_H
