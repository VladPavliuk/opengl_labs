#include <GL/glut.h>

GLfloat xRotated, yRotated, zRotated;


void drawDashLinesCube() 
{
	glColor3f(1.0, 1.0, 1.0); 

	glEnable(GL_CULL_FACE);

	glCullFace(GL_FRONT);
	glLineStipple(2, 0x00FF);
  	glEnable(GL_LINE_STIPPLE);
    glutSolidCube(1.0);
	glDisable(GL_LINE_STIPPLE);
		
	glCullFace(GL_BACK);
    glutSolidCube(1.0);


	glDisable(GL_CULL_FACE);
}

void drawDarkerLinesCube() 
{
	glEnable(GL_CULL_FACE);

	glCullFace(GL_FRONT);
	glColor3f(0.3, 0.3, 0.3); 
   	glutSolidCube(1.0);
		
	glCullFace(GL_BACK);    	
	glColor3f(1.0, 1.0, 1.0); 
	glutSolidCube(1.0);

	glDisable(GL_CULL_FACE);
}

void redisplayFunc(void)
{
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(0.0,0.0,-5.0);
    
    // changing in transformation matrix.
    // rotation about X axis
    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);
    // scaling transfomation 
    glScalef(1.0,1.0,1.0);
    // built-in (glut library) function , draw you a cube.

	drawDashLinesCube();

    // Flush buffers to screen
    glFlush();        
    // sawp buffers called because we are using double buffering 
    glutSwapBuffers();
}

void reshapeFunc(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

void idleFunc(void)
{
    // rotation around x axis 
    xRotated += 0.3;
    yRotated += 0.3;
    zRotated += 0.3;
    redisplayFunc();
}


int main (int argc, char **argv)
{
    //Initialize GLUT
    glutInit(&argc, argv);
    //double buffering used to avoid flickering problem in animation
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  
    // window size
    glutInitWindowSize(900,900);
    // create the window 
    glutCreateWindow("Cursova");
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    xRotated = yRotated = zRotated = 0.0;

    glClearColor(0.0,0.0,0.0,0.0);
    //Assign  the function used in events
    glutDisplayFunc(redisplayFunc);
    glutReshapeFunc(reshapeFunc);
    glutIdleFunc(idleFunc);
    //Let start glut loop
    glutMainLoop();
    return 0;
}
