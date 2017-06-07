#include"lines.h"
#include"Circle_and_Coordinates.h"
#include"CoordinateSystem.h"
#include<cmath>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<time.h>
using namespace std;

void ProperAngle(float &RA1, float &RA2, float &RA3){	// to get ideal angles for the diagram
	cout<<"proper angles"<<endl;
	while ((RA1 + RA2 + RA3) > 360){
		float temp = max(RA1, max(RA2, RA3));
		float temp1 = temp*0.75;
		if(temp == RA1)
			RA1 = temp1;
		else if(temp == RA2)
			RA2 = temp1;
		else if(temp == RA3)
			RA3 = temp1;
		cout<<RA1 + RA2 + RA3<<endl;
	}
	cout<<"proper angles finish"<<endl;
}

int main()
{
	cout<<"start"<<endl;
	point origin;
	origin.x = 0;
	origin.y = 0;
	cout<<"angles start"<<endl;
	float Array_of_Angles[360];
	for(int i=0;i<360;i++){
		Array_of_Angles[i]=i;
	}
	int length = sizeof(Array_of_Angles)/sizeof(float);
	srand(time(NULL));
	float random_angle1 = Array_of_Angles[rand()%length];
	float random_angle2 = Array_of_Angles[rand()%length];
	float random_angle3 = Array_of_Angles[rand()%length];
	cout<<"angles finish"<<endl;
	if((random_angle1 + random_angle2 + random_angle3) > 360)
		ProperAngle(random_angle1, random_angle2, random_angle3);
	cout<<"constructors start"<<endl;
	line A(origin, random_angle1);
	line B(origin, (random_angle1 + random_angle2));
	line C(origin, (random_angle1 + random_angle2 + random_angle3));
	circle O(10.0);
	cout<<"constructors finish"<<endl;
	polar_point P, Q;
	P.r = 10.0;
	P.theta = random_angle1 + 0.1;
	P.angle_correction();
	Q.r = 10.0;
	Q.theta = random_angle1 + random_angle2 - 0.1;
	Q.angle_correction();
	bool found = false;
	cout<<"mirror P start"<<endl;
	while(found == false)
	{
		mirror_P:
		polar_point P1 = A.MirrorPoint(P);
		P1.angle_correction();
		bool P1proper;
		if(P1.theta < random_angle1)
			P1proper = true;
		else if(P1.theta > (random_angle1 + random_angle2 + random_angle3))
			P1proper = true;
		else
			P1proper = false;
		polar_point P2 = B.MirrorPoint(P);
		P2.angle_correction();
		bool P2proper;
		if(P2.theta > (random_angle1 + random_angle2) && P2.theta < (random_angle1 + random_angle2 + random_angle3))
			P2proper = true;
		else
			P2proper = false;
		polar_point P12 = C.MirrorPoint(P1);
		P12.angle_correction();
		bool P12proper;
		if(P12.theta >  (random_angle1 + random_angle2) && P2.theta < (random_angle1 + random_angle2 + random_angle3))
			P12proper = true;
		else
			P12proper = false;
		if (P12proper == false || P2proper == false)
		{
			P.theta += random_angle2/100;
			goto mirror_P;
		}
		if (P1proper == false)
		{
			P.theta -= random_angle2/100;
			goto mirror_P;
		}
		cout<<"P -> ("<<P.r<<", "<<P.theta<<") P1 -> ("<<P1.r<<", "<<P1.theta<<") P2 -> ("<<P2.r<<", "<<P2.theta<<") P12 -> ("<<P12.r<<", "<<P12.theta<<")"<<endl;
		cout<<"P finish"<<endl;
		if (P2.theta != P12.theta)
		{
			cout<<"Q start"<<endl;
			mirror_Q:
			polar_point Q1 = A.MirrorPoint(Q);
			Q1.angle_correction();
			bool Q1proper;
			if(Q1.theta < random_angle1)
				Q1proper = true;
			else if(P1.theta > (random_angle1 + random_angle2 + random_angle3))
				Q1proper = true;
			else
				Q1proper = false;
			polar_point Q2 = B.MirrorPoint(Q);
			Q2.angle_correction();
			bool Q2proper;
			if(Q2.theta > (random_angle1 + random_angle2) && Q2.theta < (random_angle1 + random_angle2 + random_angle3))
				Q2proper = true;
			else
				Q2proper = false;
			polar_point Q12 = C.MirrorPoint(Q1);
			Q12.angle_correction();
			bool Q12proper;
			if(Q12.theta >  (random_angle1 + random_angle2) && Q2.theta < (random_angle1 + random_angle2 + random_angle3))
				Q12proper = true;
			else
				Q12proper = false;
			if (Q2proper == false)
			{
				Q.theta -= random_angle2/100;
				goto mirror_Q;
			}
			if (Q12proper == false || Q1proper == false)
			{
				Q.theta += random_angle2/100;
				goto mirror_Q;
			}
			
			cout<<"Q -> ("<<Q.r<<", "<<Q.theta<<") Q1 -> ("<<Q1.r<<", "<<Q1.theta<<") Q2 -> ("<<Q2.r<<", "<<Q2.theta<<") Q12 -> ("<<Q12.r<<", "<<Q12.theta<<")"<<endl;
			cout<<"Q finish"<<endl;
			if(Q2.theta != Q12.theta)
			{
				polar_point pq;
				pq.theta = (P.theta + Q.theta)/2;
				pq.r = P.r;
				pq.angle_correction();
				//if(condition)
				//P/Q.theta = pq.theta;
				//else
				//Q/P.theta = pq.theta;
				//P/Q.angle_correction();
			}
			else
				found = true;
		}
		else
			found = true;
	}
	cout<<"mirror finish"<<endl;
}
