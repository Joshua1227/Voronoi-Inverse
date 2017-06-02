#include<cmath>
#include<iostream>
using namespace std;
#include"CoordinateSystem.cpp"

class line{
	private:
	point start;			//the starting point of the line
	float direction;		//angle of the slope of the line
	public:
	line();
	line(point begin);
	line(float angle);
	line(point begin, float angle);	// constructors
	polar_point MirrorPoint(polar_point p);	
	point MirrorPoint(point p);		// to find the mirror image of a point on a line
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
	start = begin;
	cout<<"enter the angle at which the line is inclined"<<endl;
	cin>>direction;
}

line::line(point begin, float angle){
	start = begin;
	direction = angle;
}

polar_point line::MirrorPoint(polar_point p){
	float angle_diff = p.theta - direction;
	polar_point q;
	q.theta = direction - anfle_diff;
	q.r = p.r;
	return q;
}

point line::line(point p){
	polar_point q = ConvertToPolar(p);
	q = MirrorPoint(q);
	return ConvertToCoordinate(q);
}
