/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Computational Geometry 
** (Fall 2014) at Aarhus Univerity Denmark. 
**
** INC_CH.h
** Implementation of the incremental convex hull algorithm discussed in class
** (the one discussed in pages 6 and 7 of BKOS)
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#include "INC_CH.h"
#include <math.h>

inline int ccw(point *p1, point *p2, point *p3) {
	double left  = (p1->x - p3->x)*(p2->y - p3->y);
	double right = (p1->y - p3->y)*(p2->x - p3->x);

	double res = left - right;

	
	return res > 0;
}

inline void INC_CH::convexHull(std::deque<point>& points, const int numPoints, std::deque<point> &result) {
	std::deque<point> LUpper;	/* List of upper hull points */
	std::deque<point> LLower;	/* List of lower hull points */

	point last, middel, first; /* The last three points on stack */
	
	/* Sort the points by x-coordinate */
	std::sort(points.begin(), points.end(), point_cmp_x());
	/* Put the points p1 and p2 in a list L_Upper, with p1 as the first point */
	LUpper.push_front(points[0]);
	LUpper.push_front(points[1]);
	
	for(int i = 2; i < numPoints; i++) {
		/* Append p_i to upper list */
		LUpper.push_front(points[i]);
		while(LUpper.size() > 2) {
			/* While upper list contains more than two points */
			/* And the last three points do not make a right turn */
			first = LUpper.front(); LUpper.pop_front();
			middel = LUpper.front(); LUpper.pop_front();
			last = LUpper.front(); 

			if(ccw(&first, &middel, &last)) {
				/* BREAK if the last three points make a right turn */
				LUpper.push_front(middel);
				LUpper.push_front(first);
				break;
			} else {
				/* Otherwise remove the middle and continue */
				LUpper.push_front(first);
			}
		}
	}
	
	/* Put p_n and p_n-1 in lower list with p_n as first point */
	LLower.push_front(points[numPoints - 1]);
	LLower.push_front(points[numPoints - 2]);
	
	for(int i = numPoints - 3; i >= 0; i--) {
		/* Append p_i to upper list */
		LLower.push_front(points[i]);
		
		while(LLower.size() > 2) {
			first = LLower.front(); LLower.pop_front();
			middel = LLower.front(); LLower.pop_front();
			last = LLower.front();
			
			if(ccw(&first, &middel, &last)) {
				/* BREAK if the last three points make a right turn */
				LLower.push_front(middel);
				LLower.push_front(first);
				break;
			} else {
				/* Otherwise remove the middle and continue */
				LLower.push_front(first);
			}
		}
	}

	/* Remove first and last element in lower hull to avoid duplicates */
	LLower.pop_front();
	LLower.pop_back();
	
	
	/* Merge the two into the result */
	for(unsigned int i = 0; i < LLower.size(); i++) {
		result.push_front(LLower[i]);
	}
	for(unsigned int i = 0; i < LUpper.size(); i++) {
		result.push_front(LUpper[i]);
	}
}
