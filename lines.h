#include<cmath>
#include<iostream>
using namespace std;
#include"CoordinateSystem.h"

class line{
	private:
	point start;			//the starting point of the line
	float direction;		//angle of the slope of the line
	public:
	float angle();
	line();
	line(point begin);
	line(float angle);
	line(point begin, float angle);	// constructors
	polar_point MirrorPoint(polar_point p);	
	point MirrorPoint(point p);		// to find the mirror image of a point on a line
};
