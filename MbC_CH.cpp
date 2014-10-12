/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Computational Geometry 
** (Fall 2014) at Aarhus Univerity Denmark. 
**
** MbC_CH.cpp
** Implementation of marriage-before-conquest convex algorithm.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#include "MbC_CH.h"

void MbC_CH::upperHull(	std::deque<point>& points,	//< Points on which the CH should be computed
						const unsigned int size,	//< Size of the above
						std::deque<point> &result,	//< Result in counter-clockwise order
						std::deque<point>& erased){	//< All points not in first argument
	// Base cases
	if(size == 2) {
		// Add the one with smallest x coordinate first
		point p0 = points[0];
		point p1 = points[1];
		if(p0.x < p1.x) {
			result.push_front(p0);
			result.push_front(p1);
		} else if(p0.x == p1.x) {
			if(p0.y > p1.y) {
				result.push_front(p0);
				result.push_front(p1);				
			} else {
				result.push_front(p1);
				result.push_front(p0);			
			}
		} else {
			result.push_front(p1);
			result.push_front(p0);
		}
		// Mirror the points
		p0.x = -p0.x;
		p0.y = -p0.y;
		p1.x = -p1.x;
		p1.y = -p1.y;
		erased.push_front(p0);
		erased.push_front(p1);
		points.clear();
		return;
	} else if(size == 1) {
		// Trivial case, just add the point
		result.push_front(points[0]);
		point p = points[0];
		// Mirror the points
		p.x = -p.x;
		p.y = -p.y;
		erased.push_front(p);
		points.clear();
		return;
	} 

	/* 1. Find the point with median x coordinate p_m = (x_m, y) and partition the input into two sets P_l
	 *    and P_r where P_l contains all the points with x-coordinate smaller than x_m and P_r contains the
	 *    rest of the points
	 */
	// Find the median
	std::nth_element(points.begin(), points.begin() + size/2, points.end(), point_cmp_x());
	const double x_m = points[size/2].x;
	// Note: The splitting is done later on

	/* 2. Find the "bridge" over the vertical line X = x_m (i.e. the upper hull edge that intersects 
	 *    line X = x_m). You need to implement linear programming for this step. Let (x_i, y_i) and
	 *    (x_j, y_j) be the left and riight end points of the bridge
	 */
	// Initialize the best bridge with a point from each side of the median
	point bl = points[0]; //< best right
	point br = points[size - 1]; //< best left
	{	// Make variables only live in this scope - we do not need them later
		double alpha = (bl.y - br.y) / (bl.x - br.x);
		double beta = bl.y - alpha * bl.x;	
		// Shuffle the constraints
		std::random_shuffle(points.begin(), points.end());
		// Solve for all constraints
		const auto begin = points.begin();
		for(auto p = begin; p != points.end(); p++) {	
			if(p->y > p->x * alpha + beta) {
				// Update with first violation.
				if(p->x < x_m) {
					alpha = (br.y - p->y)/(br.x - p->x);
					beta = p->y - alpha * p->x;
					bl = *p;
				} else {
					alpha = (bl.y - p->y)/(bl.x - p->x);
					beta = p->y - alpha * p->x;
					br = *p;
				}
				for(auto j = begin; j != p; j++) {
					// Check for new violations in
					// previous constraints
					if(j->y > j->x * alpha + beta) {
						if(j->x < p->x) {
							alpha = (p->y - j->y)/(p->x - j->x);
							beta = p->y - alpha * p->x;
							bl = *j;
							br = *p;
						} else {
							alpha = (p->y - j->y)/(p->x - j->x);
							beta = p->y - alpha * p->x;
							bl = *p;
							br = *j;
						}
					}
				}
			}
		}
	}
	/* 3. Prune the points that lie under the line segment (x_i, y_i),(x_j, y_j) (these will be the
	 *    points whose x-coordinates lie between x_i and x_j.
	 */
	std::deque<point> Pl, Pr;
	while(!points.empty()) {
		// Get and pop first element
		point p = points.front(); points.pop_front();
		if(p.x < x_m && p.x <= bl.x) {
			// If it belongs the the left set
			// and is not under the bridge
			Pl.push_front(p);
		} else if(p.x >= x_m && p.x >= br.x) {
			// If it belongs to the right set
			// and is not under the bridge
			Pr.push_front(p);
		} else {
			p.x = -p.x;
			p.y = -p.y;
			erased.push_front(p);
		}
	}



	/* 4. Recursively compute the upper hill of P_l and P_r
	 */
	upperHull(Pl, Pl.size(), result, erased);
	upperHull(Pr, Pr.size(), result, erased);
}

inline void MbC_CH::convexHull(std::deque<point>& points, const int numPoints, std::deque<point> &result) {
	// Holds the points with negated x's and y's
	std::deque<point> erased;
	// Compute the upper hull
	upperHull(points, numPoints, result, erased);
	// Remove last point - it will be added soon
	result.pop_front();
	// Compute the 'upper' hull in the mirrored set of points
	upperHull(erased, numPoints, result, points);
	// Remove first element
	result.pop_back();
	// Make it clock-wise
	std::reverse(result.begin(), result.end());
}
