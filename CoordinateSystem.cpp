struct point{
	float x,y; 						//  cartesian coordinates
};
struct polar_point{  						//  polar coordinates
	float r, theta; 
};
float DegreesToRadian(float deg){
	return deg*M_PI/180;
}
point ConvertToCoordinate(polar_point p){		// A function to convert polar coordinates to cartesian coordinates
	point q;
	q.x = p.r*cos(DegreesToRadian(p.theta));
	q.y = p.r*sin(DegreesToRadian(p.theta));
	return q;
}

polar_point ConvertToPolar(point p){			// A function to convert cartesian cooredinates to polar cooordinates
	polar_point q;
	q.r = sqrt(pow(p.x, 2.0) + pow(p.y, 2.0));
	q.theta = atan2(p.y, p.x) * 180/M_PI;
	return q;
}
