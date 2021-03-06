#include"CoordinateSystem.h"
float DegreesToRadian(float deg){
	return deg*M_PI/180;
}
point polar_point::ConvertToCoordinate(){		// A function to convert polar coordinates to cartesian coordinates
	point q;
	q.x = r*cos(DegreesToRadian(theta));
	q.y = r*sin(DegreesToRadian(theta));
	return q;
}

polar_point point::ConvertToPolar(){	// A function to convert cartesian cooredinates to polar cooordinates
	polar_point q;
	q.r = sqrt(pow(x, 2.0) + pow(y, 2.0));
	q.theta = atan2(y, x) * 180/M_PI;
	return q;
}

void polar_point::angle_correction(){
	while(theta >= 360)
		theta = theta - 360;
	while (theta < 0)
		theta = theta + 360;
}


