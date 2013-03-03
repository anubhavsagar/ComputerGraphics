#include<cstdlib>
#include<cstdio>
#include<GL/gl.h>
#include<GL/glut.h>
#include<GL/glu.h>

#define WIDTH 640.0
#define HEIGHT 480.0

#define X0 10
#define Y0 260
#define X1 400
#define Y1 60

void myInit()
{
     glClearColor(1.0,1.0,1.0,1.0); // set white bg color
     glColor3f(0.0,0.0,0.0);           // set drawing color
     glPointSize(4.0);                  // a dot is 4by4 pixel
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(0.0,640.0,0.0,480.0);
}

void printPoints(int type, int pseudo, int x0, int x1, int y0, int y1)
{
//type: The actual type of line according to the value of slope (Can Take Values 1-4)
//pseudo: The type to which we want to Map the line, so as to later take its reflection (Can take Values 1 and 2)

  int dx=x1-x0;
	int dy=y1-y0;
	int incrE = 2*dy; 
	int incrNE= 2*(dy-dx);
	int incrNE2= 2*(dx-dy);
	int incrN = 2*dx;

	int x=x0,y=y0;
	
	if (type == 1 || type == 2)
	glVertex2i(x,y);
	else // Reflection being taken for the line in 1st quadrant to get the line in 2nd quadrant
	glVertex2i(WIDTH-x, y);

	int d;
	if (pseudo == 1 ) d=2*dy-dx;
	else d = 2*dx-dy;
		
  	while(x<x1 )
	{
		// incrE added to d because the point on X axis is chosen
		if(d<=0)	
		{
			if (pseudo == 1)        
			d=d+incrE;
			else
			d=d+incrN;
		}
		// incrNE is added to d because NE point was chosen
		else
		{
			if (pseudo == 1)
			{ 
   	    	 	d=d+incrNE;
        		y++;
			}
			else
			{
				d = d+ incrNE2;
				x++;
			}
		}
		// Increment of x or y depending on whether m is less or greater than 1
			
		if (pseudo == 1) x++;
		else y++;
			
		if (type == 1 || type == 2)
		glVertex2i(x,y);
		else
		glVertex2i(WIDTH-x,y);		
	}
}

void myDisplay()
{
     
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
      
	int x0=X0;
	int y0=Y0;
	int x1=X1;
	int y1=Y1;
    
	if (x0 > x1)
	{
	// Swap the points so that starting point's x is less than the other point
		int temp = x0;
		x0 = x1;
		x1 = temp;
		temp = y0;
		y0 = y1;
		y1 = temp;
	}

	// Calculate slope of the line
	int dx=x1-x0;
	int dy=y1-y0;
	float m=(float)dy/(float)dx;	

	fprintf(stdout, "m = %f\n", m);	
	fflush(stdout);
	// Set the variable type depending on the quadrant in which the slope lies
	int type, pseudo;
	if (m > 1){
	type = 2;
	pseudo = 2;
	}
	else if (m >= 0 && m <= 1){
	type = 1;
	pseudo = 1;
	}
	else if (m >=-1 && m < 0){
	type = 4;
	pseudo = 1;
	}
	else{
	type = 3;
	pseudo = 2;
	}
	
	fprintf(stdout, "Type: %d\n", type);	
	fflush(stdout);

	int incrE = 2*dy; 
	int incrNE= 2*(dy-dx);
	int incrNE2= 2*(dx-dy);
	int incrN = 2*dx;

	if (type == pseudo)
	printPoints(type, pseudo, x0, x1, y0, y1);
	else
	printPoints(type, pseudo, WIDTH-x1, WIDTH - x0, y1, y0);
	
	glEnd();
	glFlush();
}

int main(int argc, char ** argv)
{
     
     
     
     glutInit(&argc,argv);       //Initialize the toolkit
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
     glutInitWindowSize(WIDTH, HEIGHT);                 // set window size
     glutInitWindowPosition(50,50);             // set window position
     glutCreateWindow("Assignment 1: q1");
     glutDisplayFunc(myDisplay);
     myInit();
     glutMainLoop();                            // go into a perpetual loop
     return EXIT_SUCCESS;
}     

