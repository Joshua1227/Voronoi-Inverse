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

//typedef std::numeric_limits< float > dbl;

using namespace std;

point last, last1, last2, lineA, lineB, lineC;

float change_domain(float a){
	if(a < 180.0)
		return (360.0 + a);
	else 
		return a;
}

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
	float random_angle1;// = Array_of_Angles[rand()%length];	// get random angles
	float random_angle2;// = Array_of_Angles[rand()%length];
	float random_angle3;// = Array_of_Angles[rand()%length];
	cout<<"enter angles"<<endl;
	cin>>random_angle1>>random_angle2>>random_angle3;
	cout<<"angles finish"<<endl<<"The angles are:"<<endl;
	cout<<random_angle1<<endl<<random_angle2<<endl<<random_angle3<<endl;
	cout<<"constructors start"<<endl;
	line A(origin, random_angle1);					// define the lines
	line B(origin, random_angle2);
	line C(origin, random_angle3);
	circle O(10.0);							// define the circle
	cout<<"constructors finish"<<endl;
	polar_point P, Q;						// define the initial points
	P.r = 10.0;
	P.theta = random_angle1;
	P.angle_correction();
	Q.r = 10.0;
	Q.theta = random_angle2 ;
	Q.angle_correction();
	ofstream outfile;
	outfile.open("file.txt",ios::out | ios::trunc);
	bool found = false;
	while(found == false)						// start seach loop
	{
		polar_point P1 = A.MirrorPoint(P);
		polar_point P2 = B.MirrorPoint(P);
		polar_point P12 = C.MirrorPoint(P1);
		point temp,temp1,temp2,temp12;
		temp = P.ConvertToCoordinate();
		temp1 = P1.ConvertToCoordinate();
		temp2 = P2.ConvertToCoordinate();
		temp12 = P12.ConvertToCoordinate();
		outfile<<"P -> ("<<P.r<<", "<<P.theta<<") P1 -> ("<<P1.r<<", "<<P1.theta<<") P2 -> ("<<P2.r<<", "<<P2.theta<<") P12 -> ("<<P12.r<<", "<<P12.theta<<")"<<endl;
		//KEY AREA//
		if (P2.theta !=   P12.theta)			// if P is not the vertex
		{
			mirror_Q:
			polar_point Q1 = A.MirrorPoint(Q);
			polar_point Q2 = B.MirrorPoint(Q);
			polar_point Q12 = C.MirrorPoint(Q1);	// initialize Q and its mirror points
			point temp,temp1,temp2,temp12;
			temp = Q.ConvertToCoordinate();		// store them in a temporary variable
			temp1 = Q1.ConvertToCoordinate();
			temp2 = Q2.ConvertToCoordinate();
			temp12 = Q12.ConvertToCoordinate();
			outfile<<"Q -> ("<<Q.r<<", "<<Q.theta<<") Q1 -> ("<<Q1.r<<", "<<Q1.theta<<") Q2 -> ("<<Q2.r<<", "<<Q2.theta<<") Q12 -> ("<<Q12.r<<", "<<Q12.theta<<")"<<endl;
			//KEY AREA//
			
			if(Q2.theta != Q12.theta) 		// if Q is not the vertex
			{
				polar_point pq;
				pq.theta = (P.theta + Q.theta)/2;
				pq.r = P.r;
				polar_point pq1 = A.MirrorPoint(pq);
				polar_point pq2 = B.MirrorPoint(pq);
				polar_point pq12 = C.MirrorPoint(pq1);
				outfile<<"PQ -> ("<<pq.r<<", "<<pq.theta<<") PQ1 -> ("<<pq1.r<<", "<<pq1.theta<<") PQ2 -> ("<<pq2.r<<", "<<pq2.theta<<") PQ12 -> ("<<pq12.r<<", "<<pq12.theta<<")"<<endl;
				if(pq.theta == P.theta || pq.theta == Q.theta){ // if the points P and Q converge last will hold the coordinates of the voronoi points we have so far
					cout<<"final point reached"<<endl;
					outfile<<"final point reached"<<endl;
					last = P.ConvertToCoordinate();
					last1 = P1.ConvertToCoordinate();
					last2 = P2.ConvertToCoordinate();
					break;
				}
	// This section runs when the angles are split between the first and the fourth quadrant
				if(((P12.theta <= 90.0) && (P2.theta >= 180.0)) || ((Q12.theta >= 180.0)  && (Q2.theta <= 90.0)))
				{
					if(signbit(change_domain(pq2.theta) - change_domain(pq12.theta)) == signbit(change_domain(Q2.theta) - change_domain(Q12.theta))){ // this condition is when the sign of the difference between 2 and 12 for pq is the same as Q
						outfile<<"case 1.1"<<endl;
						Q.theta = pq.theta;
					}
					else if(signbit(change_domain(pq2.theta) - change_domain(pq12.theta)) == signbit(change_domain(P2.theta) - change_domain(P12.theta))){ // this condition is when the sign of the difference between 2 and 12 for pq is the same as P
						outfile<<"case 2.1"<<endl;
						P.theta = pq.theta;
					}
					else{
						cout<<"somethings wrong"<<endl;
						exit(0);
					}
				}
	// This section runs for all other cases
				else
				{
				if(signbit(pq2.theta - pq12.theta) == signbit(P2.theta - P12.theta)){
				// this condition is when the sign of the difference between 2 and 12 for pq is the same as P
					outfile<<"case 1"<<endl;
					P.theta = pq.theta;
				}
				else if(signbit(pq2.theta - pq12.theta) == signbit(Q2.theta - Q12.theta)){
				// this condition is when the sign of the difference between 2 and 12 for pq is the same as Q
					outfile<<"case 2"<<endl;
					Q.theta = pq.theta;
				}
				else{
					cout<<"somethings wrong"<<endl;
					exit(0);
				}
				}
			}
			else
				{
					found = true;
					//last variables hold the finalised voronoi points
					last = Q.ConvertToCoordinate();
					last1 = Q1.ConvertToCoordinate();
					last2 = Q2.ConvertToCoordinate();
					outfile.close();
				}
		}
		else
			{
				found = true;
				//last variables hold the finalised voronoi points
				last = P.ConvertToCoordinate();
				last1 = P1.ConvertToCoordinate();
				last2 = P2.ConvertToCoordinate();
				outfile.close();
			}
	}
	polar_point temp;
	temp.theta = A.angle();
	temp.r = 11;
	//line A, B, C are the final lines to be drawn which represent the voronoi diagram
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
