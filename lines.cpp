#include<cmath>
#include"lines.h"
#include<iostream>
using namespace std;
#include"CoordinateSystem.h"

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
	cout<<"start point of line is ("<<start.x<<", "<<start.y<<")"<<endl;
	cout<<"direction of the line is "<<direction<<endl;
}

polar_point line::MirrorPoint(polar_point p){
	float angle_diff = p.theta - direction;
	polar_point q;
	q.theta = direction - angle_diff;
	q.r = p.r;
	q.angle_correction();
	return q;
}

point line::MirrorPoint(point p){
	polar_point q = p.ConvertToPolar();
	q = MirrorPoint(q);
	return q.ConvertToCoordinate();
}
