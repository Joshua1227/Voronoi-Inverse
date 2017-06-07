#include"Circle_and_Coordinates.h"
#include<iostream>
using namespace std;
#include<cmath>
#include"CoordinateSystem.h"

circle::circle(){
	cout<<"enter the x coordinate of the center of the circle"<<endl;
	cin>>center.x;
	cout<<"enter the y coordinate of the center of the circle"<<endl;
	cin>>center.y;
	cout<<"enter the radius of the circle"<<endl;
	cin>>radius;
	cout<<"center of the circle is ("<<center.x<<", "<<center.y<<")"<<endl;		//for testing
	cout<<"radius of the circle is "<<radius<<endl;					//for testing
}

circle::circle(point p){
	center.x = 0;
	center.y = 0;
	radius = sqrt(pow((center.x - p.x),2) + pow((center.y - p.y),2));
	cout<<"center of the circle is ("<<center.x<<", "<<center.y<<")"<<endl;		//for testing
	cout<<"radius of the circle is "<<radius<<endl;					//for testing
}

circle::circle(float rad){
	center.x = 0;
	center.y = 0;
	radius = rad;
	cout<<"center of the circle is ("<<center.x<<", "<<center.y<<")"<<endl;		//for testing
	cout<<"radius of the circle is "<<radius<<endl;					//for testing
}
bool circle::IsPointOnCircle(point &p){				// Check whether point is on the circle
	bool found = false;					
	float temp;
	if (sqrt(pow((center.x-p.x),2) + pow((center.y-p.y),2)) == radius)	//the radius of the circle is thae same as the distance between the center and the point
		found = true;
	else if(sqrt(pow((center.x-p.x),2) + pow((center.y-p.y),2)) < radius +1 && sqrt(pow((center.x-p.x),2) + pow((center.y-p.y),2)) > radius - 1)	//  if there is very little distance between the the distance and radius replace the point with the closest point on the circle
		{
			p = ClosestPoint(p);
			found = true;
		}
	return found;
}

bool circle::IsPointOnCircle(polar_point &p){
	bool found = false;
	if (center.x == 0 && center.y ==0)
	{
		if(p.r == radius)
			found = true;
	}
	/*else						// else convert point to cartesian coordinate and then check
	{
		point p1 = ConvertToCoordinate(p);
		found = IsPointOnCircle(p1);
	}*/						//  need alternate code to transform center of circle and then check if it lies on the circle
	if (found == false && p.r > radius - 1 && p.r < radius + 1)
	{
		p.r = radius;
		found = true;
	}
	return found;
}

point circle::MidPointOnCircle(polar_point p, polar_point q){
	if(!IsPointOnCircle(p) || !IsPointOnCircle(q) )
	{
		cerr<<"the polar point(s) ("<<p.r<<", "<<p.theta<<") and/or ("<<q.r<<", "<<q.theta<<") do not lie on the circle"<<endl;
	}							//check whether p and q lie on the circle
	polar_point f;						
	point f1;
	float tempx = center.x;
	float tempy = center.y;
	if (center.x == 0 && center.y == 0)
	{
		f.theta = (p.theta + q.theta)/2;
		f.r = p.r;
		f.angle_correction();
	}
	else
	{
		center.x -= tempx;			// transform center of the circle to the origin				
		center.y -= tempy;
		point p1 = p.ConvertToCoordinate();	// convert polar point to coordinate for tranforming
		point q1 = q.ConvertToCoordinate();
		p1.x -= tempx;				// transform the points
		p1.y -= tempy;
		q1.x -= tempx;
		q1.y -= tempy;
		polar_point p2 = p1.ConvertToPolar();	// convert coordinate points to polar for finding mid point.
		polar_point q2 = q1.ConvertToPolar();
		p2.angle_correction();
		q2.angle_correction();
		f.theta = (p2.theta + q2.theta)/2;
		f.r = p2.r;
		f.angle_correction();
		center.x += tempx;			// transform center of the circle from the origin to its original location				
		center.y += tempy;
	}
	f1 = f.ConvertToCoordinate();
	f1.x += tempx;
	f1.y += tempy; 
	return f1;
}

point circle::MidPointOnCircle(point p, point q){
	if(!IsPointOnCircle(p) || !IsPointOnCircle(q) )
	{
		cout<<"the point(s) ("<<p.x<<", "<<p.y<<") and/or ("<<q.x<<", "<<q.y<<") do not lie on the circle"<<endl;
	}				// check whether points are on circle
	polar_point f;
	point f1;
	float tempx = center.x;
	float tempy = center.y;
	if(center.x == 0, center.y == 0)
	{
		polar_point p1 = p.ConvertToPolar();
		polar_point q1 = q.ConvertToPolar();
		p1.angle_correction();
		q1.angle_correction();
		f.theta = (p1.theta + q1.theta)/2;
		f.r = p1.r;
		f.angle_correction();
	}
	else
	{
		center.x -= tempx;				// transforming center of the circle to the origin
		center.y -= tempy;
		p.x -= tempx;					// tranform points
		p.y -= tempy;
		q.x -= tempx;
		q.y -= tempy;
		polar_point p1 = p.ConvertToPolar(); 		// convert tranformed points to polar coordinates
		polar_point q1 = q.ConvertToPolar();
		p1.angle_correction();
		q1.angle_correction();
		f.theta = (p1.theta + q1.theta)/2;		// calculate midpoint in transformed coordinate system
		f.r = p1.r;
		p.x += tempx; 					// transform points and center back to their original position
		p.y += tempy;
		q.x += tempx;
		q.y += tempy;
		center.x += tempx;				
		center.y += tempy;
	}
	f1 = f.ConvertToCoordinate();				// convert midpoint to cartesian coordinate 
	f1.x += tempx;						// transform the midpoint to original coordinate system
	f1.y += tempy;
	return f1;
}

point circle::ClosestPoint(point p){				// this function assumes center of the circle is at the origin
	polar_point p1 = p.ConvertToPolar();
	p1.r = radius;
	p1.angle_correction();
	p = p1.ConvertToCoordinate();
	return p;
}

polar_point circle::ClosestPoint(polar_point p){		// this function assumes center of the circle is at the origin
	p.r = radius;
	return p;
}
