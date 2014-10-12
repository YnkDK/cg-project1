/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Computational Geometry 
** (Fall 2014) at Aarhus Univerity Denmark. 
**
** DC_CH.cpp
** Implementation of a divide-and-conquer convex algorithm.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#include "DC_CH.h"
#include <iostream>

//<0 p1p2, p2p3 left turn, >0 right turn, 0 same line segment
inline double ccw2(point *p1, point *p2, point *p3) {
	     double left  = (p1->x - p3->x)*(p2->y - p3->y);
	     double right = (p1->y - p3->y)*(p2->x - p3->x);
	     return left-right;
}
	

std::deque<point> DC_CH::findConvexHull(int left, int right, std::deque<point>& points){

  /*
   * Base case.
   * In case we have at most 3 points, then all the points are part of the convex hull.
   * All the points are stored in a clockwise order, so we must be careful.
   * 
   */
  
  int dist = right-left + 1;
  
  if(dist <= 2){
    
    std::deque<point> cHull;
    
    for(int i=left;i<=right;i++)
      cHull.push_back(points[i]);
    
    return  cHull;
    
  }
  else if(dist == 3){
    //ensure that the points are stored in clockwise order
    std::deque<point> cHull;
    point *p1, *p2, *p3;
    p1 = &points[left];
    p2 = &points[left+1];
    p3 = &points[left+2];
    double tmp = ccw2(p1, p2 , p3);
   
    if(tmp < 0){ //right turn
      
      /*
       *         p2
       *         /\
       *        /  \
       *       /   p3
       *      /    
       *    p1
       *  
       *  the direction is from p1 to p2 and from p2 to p3.
       * 
       */
      
      cHull.push_back(*p1);
      cHull.push_back(*p2);
      cHull.push_back(*p3);
     // std::cout<<p1->x<<" "<<p1->y<<" "<<p2->x<<" "<<p2->y<<" "<<p3->x<<" "<<p3->y<<std::endl;
    
    }
    else if(tmp > 0){ //left turn
  
       /*
       *         
       *  p3-----p2
       *        / 
       *       /   
       *      /    
       *    p1
       *  
       *  the direction is from p1 to p2 and from p2 to p3.
       * 
       */
       
	cHull.push_back(*p1);
	cHull.push_back(*p3);
	cHull.push_back(*p2);
        //std::cout<<p1->x<<" "<<p1->y<<" "<<p3->x<<" "<<p3->y<<" "<<p2->x<<" "<<p2->y<<std::endl;
    
   }
   else{
   
      
      /* 
       * 
       * p1-------p2-------p3
       *  
       * the direction is from p1 to p2 and from p2 to p3.
       * 
       * 
       * In this case, we remove the middle point. 
       * Claim: The middle point is always p2.
       * Proof: If p1,p2,p3 are on a horizontal line, they are sorted by their x  coordinate so p2 is the middle point.
       * If p1,p2,p3 are on a vertical line, they have the same x value, but then they are also sorted by their y value but in an descending order. So p3 => p2 => p1.
       * 
       */
     
      cHull.push_back(*p1);
      cHull.push_back(*p3);
      
   }
    
    return cHull;
  
  }
  
  //find mean
  
  int mean = (left+right)/2;
  
  //divide the problem to two sub problems
  std::deque<point> leftConvexHull = findConvexHull(left, mean, points);
  std::deque<point> rightConvexHull = findConvexHull(mean+1, right, points);
  int leftCHsize = leftConvexHull.size();
  int rightCHsize = rightConvexHull.size();
  
  
  //now we apply a sequential algorithm to merge these two convex hulls
  
  //find the indexes of the rightmost point of left convex hull and left most point of right convex hull
  int lowerTangentPointOfLCV = getRightMostPoint(leftConvexHull);
  int lowerTangentPointOfRCV = getLeftMostPoint(rightConvexHull);
   
  /*
   * 
   * Finding the lower tangent of the two convex hulls
   * The idea is, having the line defined by the two initial points (lowerTangentPointOfLCV => lowerTangentPointOfRCV), we sequentially try to guide this line, either by moving clockwise
   * in the left hall, or moving counter clockwise in the right hull, to the lower tangent that we want to find.
   * 
   */
  
   bool done = false;
   
   //define the two indexes that are going to be used to scan the two convex hulls
   int i1 = lowerTangentPointOfLCV + 1;
   int init1 = lowerTangentPointOfLCV;
   int init2 = lowerTangentPointOfRCV;
   if(i1 == leftCHsize) i1 = 0;
   int i2 = lowerTangentPointOfRCV - 1;
   if(i2 < 0) i2 = rightCHsize-1;
   
   while(!done){
     
    done = true;
    
    double tmp = ccw2(&leftConvexHull[lowerTangentPointOfLCV], &rightConvexHull[lowerTangentPointOfRCV], &leftConvexHull[i1]);
    
    if(tmp <= 0 && i1!=init1){
        
	done = false;
	lowerTangentPointOfLCV = i1;
	i1++;
	if(i1 == leftCHsize) i1 = 0;
	
    }
    
    tmp = ccw2(&rightConvexHull[lowerTangentPointOfRCV], &leftConvexHull[lowerTangentPointOfLCV], &rightConvexHull[i2]);
    
    if(tmp >=0 && i2!=init2){
      
	done = false;
	lowerTangentPointOfRCV = i2;
	i2--;
	if(i2 < 0) i2 = rightCHsize-1;
    }
    
     
   }
    /*
   * 
   * Finding the upper tangent of the two convex hulls
   * 
   */
  
   int upperTangentPointOfLCV = getRightMostPoint(leftConvexHull);
   int upperTangentPointOfRCV = getLeftMostPoint(rightConvexHull);
   init1 = upperTangentPointOfLCV;
   init2 = upperTangentPointOfRCV;
   i1 = upperTangentPointOfLCV - 1;
   if(i1 < 0) i1 = leftCHsize - 1;
   i2 = upperTangentPointOfRCV + 1;
   if(i2 == rightCHsize) i2 = 0;
   
   done = false;
   while(!done){
    done = true;
    
    double tmp = ccw2(&leftConvexHull[upperTangentPointOfLCV], &rightConvexHull[upperTangentPointOfRCV], &leftConvexHull[i1]);

    if(tmp >= 0 && i1!=init1){
      
	done = false;
	upperTangentPointOfLCV = i1;
	i1--;
	if(i1 < 0) i1 = leftCHsize-1;
      
    }
    
    tmp = ccw2(&rightConvexHull[upperTangentPointOfRCV], &leftConvexHull[upperTangentPointOfLCV], &rightConvexHull[i2]); 
   
    if(tmp <= 0 && i2!=init2){
      
	done = false;
	upperTangentPointOfRCV = i2;
	i2++;
	if(i2 == rightCHsize) i2 = 0;
    }
     
   }
   /*
    * 
    * Final part of the merging.
    *
    *
    * */
   
   //start travelling from the upper tangent point in the left convex hull, follow the clockwise direction.
  
   std::deque<point> totalConvexHull;
   
   totalConvexHull.push_back(leftConvexHull[upperTangentPointOfLCV]);
   totalConvexHull.push_back(rightConvexHull[upperTangentPointOfRCV]);
   
   if(upperTangentPointOfRCV!=lowerTangentPointOfRCV){
     
      int i = upperTangentPointOfRCV+1;
      if(i == rightCHsize) i = 0;
      
      while(rightConvexHull[i].label != rightConvexHull[lowerTangentPointOfRCV].label){
   	totalConvexHull.push_back(rightConvexHull[i]);
	i++;
	if(i == rightCHsize) i = 0;
      } 
      
      totalConvexHull.push_back(rightConvexHull[lowerTangentPointOfRCV]);
	  
   }
   
   if(lowerTangentPointOfLCV != upperTangentPointOfLCV){
    
      totalConvexHull.push_back(leftConvexHull[lowerTangentPointOfLCV]);
      int i = lowerTangentPointOfLCV + 1;
      if(i == leftCHsize) i = 0;
   
      while(leftConvexHull[i].label != leftConvexHull[upperTangentPointOfLCV].label){
	totalConvexHull.push_back(leftConvexHull[i]);
	i++;
	if(i == leftCHsize) i = 0;
     
      }
   
   }
   
   return totalConvexHull;

}


inline void DC_CH::convexHull(std::deque<point>& points, const int numPoints, std::deque<point> &result) {

  
  sort(points.begin(), points.end(), point_cmp_x());
  result = findConvexHull(0, numPoints-1, points);
  
}
