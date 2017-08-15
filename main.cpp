#include"lines.h"
#include"Circle_and_Coordinates.h"
#include"CoordinateSystem.h"
#include<cmath>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<time.h>
#include<cstdlib>
#include<GL/glut.h>
#include<fstream>
#include<iomanip>
//#include<limits>

//typedef std::numeric_limits< float > dbl;

using namespace std;

point last, last1, last2, lineA, lineB, lineC;

void mydisplay()
{
	const float PI=3.14159;

	//fill the frame buffer with the background color
	glClear(GL_COLOR_BUFFER_BIT);

	//fill a circle using a different color for each point
	//You get totally different drawings using the drawing
	//modes GL_POLYGON and GL_TRIANGLE_FAN
	//glBegin(GL_POLYGON);
	glBegin(GL_LINE_LOOP);
	//fill a circle using a triangle fan
	//glBegin(GL_TRIANGLE_FAN);
		//All triangles fan out starting with this point
		glVertex2f (0.0,0.0);
		for (float i = 0; i <=360; i+= 0.0001)
		{				
			glColor3f(255, 255, 255);
			glVertex2f(10.0*cos(i*PI/180), 10.0*sin(i*PI/180));
		}
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(0, 50);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(50, 0);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(-50, 0);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(0, -50);
	glEnd();
	glFlush();
	glLineWidth(1.0); 
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(lineA.x, lineA.y);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(lineB.x, lineB.y);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(lineC.x, lineC.y);
	glEnd();
	glEnable(GL_POINT_SMOOTH);
	glPointSize(4.0);
	glColor3f(0,255,0);
	glBegin(GL_POINTS);
		glVertex2f(last.x,last.y);
	glEnd();
	glBegin(GL_POINTS);
		glVertex2f(last1.x,last1.y);
	glEnd();
	glBegin(GL_POINTS);
		glVertex2f(last2.x,last2.y);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	//flush the buffer so the circle displays
	//immediately
	glColor3f(255,255,255);
	glFlush();
}


//
// Function Name:  init()
//
// This function initializes several of
// OpenGL's state variables.  Namely it
// sets the background color, the fill
// color, and sets up the "real" world
// coordinate system.

void init()
{
	//set the background color to black
	glClearColor (0.0, 0.0, 0.0, 0.0);

	//set the draw/fill color to white
	glColor3f(1.0, 0.0, 0.0);

	//set the "real" world coordinates
	//to a window from -2.5 to 2.5 in x and
	//-2.5 to 2.5 in y
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D(-10.5,10.5,-10.5,10.5);
}

void ProperAngle(float &RA1, float &RA2, float &RA3){	// to get ideal angles for the diagram
	//cout<<"proper angles"<<endl;
	while ((RA1 + RA2 + RA3) > 360){
		float temp = max(RA1, max(RA2, RA3));
		float temp1 = temp*0.75;
		if(temp == RA1)
			RA1 = temp1;
		else if(temp == RA2)
			RA2 = temp1;
		else if(temp == RA3)
			RA3 = temp1;
		//cout<<RA1 + RA2 + RA3<<endl;
	}
	//cout<<"proper angles finish"<<endl;
}

int main(int argc, char** argv)
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
	float random_angle1 = Array_of_Angles[rand()%length];	// get random angles
	float random_angle2 = Array_of_Angles[rand()%length];
	float random_angle3 = Array_of_Angles[rand()%length];
	cout<<"enter angles"<<endl;
	cin>>random_angle1>>random_angle2>>random_angle3;
	cout<<"angles finish"<<endl<<"The angles are:"<<endl;
	if((random_angle1 + random_angle2 + random_angle3) > 360)	// make sure angles are legitimate
		ProperAngle(random_angle1, random_angle2, random_angle3);
	cout<<random_angle1<<endl<<random_angle1 + random_angle2<<endl<<random_angle1 + random_angle2 + random_angle3<<endl;
	cout<<"constructors start"<<endl;
	line A(origin, random_angle1);					// define the lines
	line B(origin, (random_angle1 + random_angle2));
	line C(origin, (random_angle1 + random_angle2 + random_angle3));
	circle O(10.0);							// define the circle
	cout<<"constructors finish"<<endl;
	polar_point P, Q;						// define the initial points
	P.r = 10.0;
	P.theta = random_angle1;
	P.angle_correction();
	Q.r = 10.0;
	Q.theta = random_angle1 + random_angle2 ;
	Q.angle_correction();
	ofstream outfile;
	outfile.open("file.txt",ios::out | ios::trunc);
	bool found = false;
	while(found == false)						// start seach loop
	{
		//cout<<"mirror P start"<<endl;
		//mirror_P:
		polar_point P1 = A.MirrorPoint(P);
		//P1.angle_correction();
		//bool P1proper;				// make sure P1 is legitimate
		//if(P1.theta < random_angle1)
		//	P1proper = true;
		//else if(P1.theta > (random_angle1 + random_angle2 + random_angle3))
		//	P1proper = true;
		//else
		//	P1proper = false;
		polar_point P2 = B.MirrorPoint(P);
		//P2.angle_correction();
		//bool P2proper;				// make sure P2 is legitimate
		//if(P2.theta > (random_angle1 + random_angle2) && P2.theta < (random_angle1 + random_angle2 + random_angle3))
		//	P2proper = true;
		//else
		//	P2proper = false;
		polar_point P12 = C.MirrorPoint(P1);
		//P12.angle_correction();
		//bool P12proper;				// make sure P12 is legitimate
		//if(P12.theta >  (random_angle1 + random_angle2) && P2.theta < (random_angle1 + random_angle2 + random_angle3))
		//	P12proper = true;
		//else
		//	P12proper = false;
		//if (P12proper == false || P2proper == false)
		//{
		//	P.theta += random_angle2/100;
			//cout<<random_angle1 + random_angle2<<endl;
			//cout<<random_angle1 + random_angle2 + random_angle3<<endl;
			//cout<<"goto p1 "<<P12.theta<<" "<<P2.theta<<endl;
		//	goto mirror_P;
		//}
		/*else if (P1proper == false)
		{
			cout<<random_angle1<<endl;
			cout<<random_angle1 + random_angle2 + random_angle3<<endl;
			P.theta -= random_angle2/100;
			cout<<"goto p2 "<<P1.theta<<" "<<endl;
			goto mirror_P;
		}*/
		//P.angle_correction();
		//P1.angle_correction();
		//P2.angle_correction();
		//P12.angle_correction();
		point temp,temp1,temp2,temp12;
		temp = P.ConvertToCoordinate();
		temp1 = P1.ConvertToCoordinate();
		temp2 = P2.ConvertToCoordinate();
		temp12 = P12.ConvertToCoordinate();
		outfile.precision(20);
		outfile<<fixed;
		//outfile<<setprecision(20)<<"P -> ("<<temp.x<<", "<<temp.y<<") P1 -> ("<<temp1.x<<", "<<temp1.y<<") P2 -> ("<<temp2.x<<", "<<temp2.y<<") P12 -> ("<<temp12.x<<", "<<temp12.y<<")"<<endl;
		outfile<<setprecision(20)<<"P -> ("<<P.r<<", "<<P.theta<<") P1 -> ("<<P1.r<<", "<<P1.theta<<") P2 -> ("<<P2.r<<", "<<P2.theta<<") P12 -> ("<<P12.r<<", "<<P12.theta<<")"<<endl;
		//cout<<"P finish"<<endl;
		//KEY AREA//
		if (P2.theta != P12.theta)			// if P is not the vertex
		{
			//cout<<"Q start"<<endl;
			mirror_Q:
			polar_point Q1 = A.MirrorPoint(Q);
			//Q1.angle_correction();
			//bool Q1proper;				// make sure Q1 is legitimate
			//if(Q1.theta < random_angle1)
			//	Q1proper = true;
			//else if(P1.theta > (random_angle1 + random_angle2 + random_angle3))
			//	Q1proper = true;
			//else
			//	Q1proper = false;
			polar_point Q2 = B.MirrorPoint(Q);
			//Q2.angle_correction();
			//bool Q2proper;				// make sure Q2 is legitimate
			//if(Q2.theta > (random_angle1 + random_angle2) && Q2.theta < (random_angle1 + random_angle2 + random_angle3))
			//	Q2proper = true;
			//else
			//	Q2proper = false;
			polar_point Q12 = C.MirrorPoint(Q1);
			//Q12.angle_correction();
			//bool Q12proper;				// make sure Q12 is legitimate
			//if(Q12.theta >  (random_angle1 + random_angle2) && Q2.theta < (random_angle1 + random_angle2 + random_angle3))
			//	Q12proper = true;
			//else
			//	Q12proper = false;
			//if (Q2proper == false)
			//{
				//cout<<random_angle1 + random_angle2<<endl;
				//cout<<random_angle1 + random_angle2 + random_angle3<<endl;
			//	Q.theta -= random_angle2/10000;
				//cout<<"goto q1 "<<Q2.theta<<" "<<endl;
			//	goto mirror_Q;
			//}
			/*else if (Q12proper == false || Q1proper == false)
			{
				cout<<random_angle1 + random_angle2<<endl;
				cout<<random_angle1 + random_angle2 + random_angle3<<endl;
				cout<<random_angle1<<endl;
				Q.theta += random_angle2/10000;
				cout<<"goto q2 "<<Q12.theta<<" "<<Q1.theta<<endl;
				goto mirror_Q;
			}*/
			//Q.angle_correction();
			//Q1.angle_correction();
			//Q2.angle_correction();
			//Q12.angle_correction();
			outfile.precision(20);
			outfile<<fixed;	
			point temp,temp1,temp2,temp12;
			temp = Q.ConvertToCoordinate();
			temp1 = Q1.ConvertToCoordinate();
			temp2 = Q2.ConvertToCoordinate();
			temp12 = Q12.ConvertToCoordinate();
			//outfile<<setprecision(20)<<"Q -> ("<<temp.x<<", "<<temp.y<<") Q1 -> ("<<temp1.x<<", "<<temp1.y<<") Q2 -> ("<<temp2.x<<", "<<temp2.y<<") Q12 -> ("<<temp12.x<<", "<<temp12.y<<")"<<endl<<endl;
			outfile<<setprecision(20)<<"Q -> ("<<Q.r<<", "<<Q.theta<<") Q1 -> ("<<Q1.r<<", "<<Q1.theta<<") Q2 -> ("<<Q2.r<<", "<<Q2.theta<<") Q12 -> ("<<Q12.r<<", "<<Q12.theta<<")"<<endl;
			//cout<<"Q finish"<<endl;
			//KEY AREA//
			
			if(Q2.theta != Q12.theta) 		// if Q is not the vertex
			{
				polar_point pq;
				pq.theta = (P.theta + Q.theta)/2;
				pq.r = P.r;
				//pq.angle_correction();
				polar_point pq1 = A.MirrorPoint(pq);
				//pq1.angle_correction();
				polar_point pq2 = B.MirrorPoint(pq);
				//pq2.angle_correction();
				polar_point pq12 = C.MirrorPoint(pq1);
				//pq12.angle_correction();
				outfile<<setprecision(20)<<"PQ -> ("<<pq.r<<", "<<pq.theta<<") PQ1 -> ("<<pq1.r<<", "<<pq1.theta<<") PQ2 -> ("<<pq2.r<<", "<<pq2.theta<<") PQ12 -> ("<<pq12.r<<", "<<pq12.theta<<")"<<endl;
				if(pq.theta == P.theta || pq.theta == Q.theta){
					cout<<"final point reached"<<endl;
					outfile<<"final point reached"<<endl;
					exit(0);
				}
				if(pq2.theta > pq12.theta){
					outfile<<"case 1"<<endl;
					//cout<<"1) "<<P.theta<<endl;
					//cout<<"1.1) "<<pq.theta<<endl;
					P.theta = pq.theta;
					//cout<<"2) "<<P.theta<<endl;
					//P.angle_correction();
				//	cout<<"3) "<<P.theta<<endl;
				}
				else if(pq2.theta < pq12.theta){
					outfile<<"case 2"<<endl;
					Q.theta = pq.theta;
					//Q.angle_correction();
				}
				else if(pq2.theta == pq12.theta){
					outfile<<"case 3"<<endl;
					P.theta = pq.theta;
					//P.angle_correction();
				}
				else{
					cout<<"somethings wrong"<<endl;
					exit(0);
				}
			}
			else
				{
					found = true;
					last = Q.ConvertToCoordinate();
					last1 = Q1.ConvertToCoordinate();
					last2 = Q2.ConvertToCoordinate();
					outfile.close();
				}
		}
		else
			{
				found = true;
				last = P.ConvertToCoordinate();
				last1 = P1.ConvertToCoordinate();
				last2 = P2.ConvertToCoordinate();
				outfile.close();
			}
	}
	//cout<<"mirror finish"<<endl;
	polar_point temp;
	temp.theta = A.angle();
	temp.r = 11;
	lineA = temp.ConvertToCoordinate();
	temp.theta = B.angle();
	lineB = temp.ConvertToCoordinate();
	temp.theta = C.angle();
	lineC = temp.ConvertToCoordinate();
		//set up a session with the window system
	glutInit(&argc, argv);

	//use a single frame buffer with red, green,
	//and blue color
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA); 

	//set the window size to 500 by 500
	glutInitWindowSize(500,500);

	//the upper left corner will appear
	//at (0,0) on the screen
	glutInitWindowPosition(0,0);

	//When the window appears it has "simple"
	//on the title bar
	glutCreateWindow("circle");

	//register the display callback to be the
	//function mydisplay
	glutDisplayFunc(mydisplay);  

	//initialize OpenGL
	init();

	//start the infinite event loop
	glutMainLoop();
}
