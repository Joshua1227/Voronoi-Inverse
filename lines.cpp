#include<cmath>
#include<iostream>
using namespace std;
#include"CoordinateSystem"

class line{
	private:
	point start;			//the starting point of the line
	float direction;		//angle of the slope of the line
	public:
	line();
	line(point begin);
	line(float angle);
	line(point begin, float angle);	// constructors
	polar_point mirrorpoint(polar_point p);	
	point mirrorpoint(point p);		// to find the mirror image of a point on a line
}

line::line(){
	cout<<"enter the x coordinate of the start point of the line"<<endl;
	cin>>start.x;
	cout<<"enter the y coordinate of the start point of the line"<<endl;
	cin>>start.y;
	cout<<"enter the angle at which the line is inclined"<<endl;
	cin>>direction;
}
line::line(point begin){
	
}
