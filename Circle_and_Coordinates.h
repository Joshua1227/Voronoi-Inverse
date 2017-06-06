#include<iostream>
using namespace std;
#include<cmath>
#include"CoordinateSystem.h"

class circle{
	private:
	float radius; 						//  radius of the circle
	point center; 						//  center of the circle 
	public:
	circle();
	circle(point p);
	circle(float rad);					//constructors	
	point ClosestPoint(point p);
	polar_point ClosestPoint(polar_point p);	// to replace a point outside a circle to the closest point on the circle
	bool IsPointOnCircle(point &p);
	bool IsPointOnCircle(polar_point &p);		// Both are functions to check whether a given point lies on the circle 
	point MidPointOnCircle(point p, point q);
	point MidPointOnCircle(polar_point p, polar_point q);	// find the midpoint on the circle of two points lying on the same circle
};
