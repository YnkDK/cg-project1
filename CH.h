/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Computational Geometry 
** (Fall 2014) at Aarhus Univerity Denmark. 
**
** CH.h
** Interface used for all convex hull algorithms implemeted.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/
#ifndef _CH_H
#define _CH_H
#include <deque> // Double-ended queue (std::deque)
#include <algorithm>
#include <iostream>
#include <cstdio> // printf
#include <algorithm> // std::sort
#include <cfloat> // DBL_EPSILON
#include <string>

struct point {
	double x;   /* x-coordinate of p_i */
	double y;   /* y-coordinate of p_i */
	int label; /* p_i has label i */
};

class CH {
public:
	virtual const char* getName() = 0;
	virtual ~CH() {/* stuff */}
	virtual void convexHull(std::deque<point>& points, const int numPoints, std::deque<point> &result) = 0;
};

struct point_cmp_x {
	/**
	* Sort in lexicographic order, i.e. first sort by x-coordinate
	* and if points have the same x-coordinate we sort by
	* y-coordinate
	*/
	inline bool operator() (const point &p1, const point &p2) {
        return (p1.x < p2.x) || (p1.x == p2.x && p1.y > p2.y);
    }
};

#endif //_CH_H
