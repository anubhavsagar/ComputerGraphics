#include<cstdlib>
#include<cstdio>
#include<GL/gl.h>
#include<GL/glut.h>
#include<GL/glu.h>

#define WIDTH 640.0
#define HEIGHT 480.0

#define RADIUS 200

void myInit()
{
     glClearColor(1.0,1.0,1.0,1.0); // set white bg color
     glColor3f(0.0,0.0,0.0);           // set drawing color
     glPointSize(4.0);                  // a dot is 4by4 pixel
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(-640.0,640.0,-480.0,480.0);
}

void drawCircle(int x,int y)
{
  glVertex2i(x,y);
	glVertex2i(y,x);
	glVertex2i(-x,y);
	glVertex2i(-y,x);
	glVertex2i(x,-y);
	glVertex2i(y,-x);
	glVertex2i(-x,-y);
	glVertex2i(-y,-x);
}

void myDisplay()
{
     
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
     
	int x=0;
	int y=RADIUS;
	int d=1-y;
	int deltaE=3;
	int deltaSE=-2*y+5;
	
	drawCircle(x,y);
	while(y>x){
		if(d<0){
			d+=deltaE;
			deltaE+=2;
			deltaSE+=2;
		}
		else{
			d+=deltaSE;
			deltaE+=2;
			deltaSE+=4;
			y--;
		}
		x++;
		drawCircle(x,y);
	}
	glEnd();
	glFlush();
}

int main(int argc, char ** argv)
{
     
     
     
     glutInit(&argc,argv);       //Initialize the toolkit
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
     glutInitWindowSize(WIDTH, HEIGHT);                 // set window size
     glutInitWindowPosition(50,50);             // set window position
     glutCreateWindow("Assignment 1: q2");
     glutDisplayFunc(myDisplay);
     myInit();
     glutMainLoop();                            // go into a perpetual loop
     return EXIT_SUCCESS;
}     

