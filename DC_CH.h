/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Computational Geometry 
** (Fall 2014) at Aarhus Univerity Denmark. 
**
** DC_CH.h
** Implementation of a divide-and-conquer convex algorithm.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#ifndef _DC_CH_H
#define _DC_CH_H

#include "CH.h"

class DC_CH : public CH {

private:

  	std::deque<point> findConvexHull(int left, int right, std::deque<point>& points);
	int getRightMostPoint(std::deque<point>& ch){
  
    		int sz = ch.size();
    		int tmp = 0;
    		for(int i=0;i<sz;i++){
    
      			if(ch[i].x > ch[tmp].x) {
				tmp = i;
      			}	
    
    		}
    		return tmp;
  	}

  	int getLeftMostPoint(std::deque<point>& ch){
  
    		int sz = ch.size();
    		int tmp = 0;
    		for(int i=0;i<sz;i++){
      			if(ch[i].x < ch[tmp].x) {
				tmp = i;
      			}
    		}
    		return tmp;
  	}
public:
	const char* getName() {
		return "DC_CH";
	}
	virtual void convexHull(std::deque<point>& points, const int numPoints, std::deque<point> &result);
	
	DC_CH() {
		
	}
};

#endif //_DC_CH_H
