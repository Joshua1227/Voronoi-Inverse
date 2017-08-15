#ifndef COORDINATE_SYSTEM
#define COORDINATE_SYSTEM
#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif
#include<cmath>
struct polar_point;
struct point{
	float x,y;				//  cartesian coordinates
	polar_point ConvertToPolar(); 
};
struct polar_point{  						//  polar coordinates
	float r, theta; 
	point ConvertToCoordinate();
	void angle_correction();
};
#endif
