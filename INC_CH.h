/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Computational Geometry 
** (Fall 2014) at Aarhus Univerity Denmark. 
**
** INC_CH.cpp
** Implementation of the incremental convex hull algorithm discussed in class
** (the one discussed in pages 6 and 7 of BKOS)
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#ifndef _INC_CH_H
#define _INC_CH_H

#include "CH.h"

class INC_CH : public CH {
public:
	const char* getName() {
		return "INC_CH";
	}
	virtual void convexHull(std::deque<point>& points, const int numPoints, std::deque<point> &result);
	
	INC_CH() {
		
	}
};

#endif //_INC_CH_H
