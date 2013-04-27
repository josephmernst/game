#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#define USING_MATH_DEFINES
#include <math.h>
#include <float.h>

#include "Object.h"
#include "Pyramid.h"
#include "MainWindow.h"

int main(int argc, char * argv[]){
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glutIdleFunc(idle);
	
	init_main_window();
	objects.clear();
	objects.push_back(new Pyramid());
	glTranslatef(2,0,0);
	objects.push_back(new Object());
	glTranslatef(2,0,0);
	objects.push_back(new Object());
	glTranslatef(-4,0,0);

	//display_main_window();
	glutMainLoop();
	
	return 0;
}
