#include "Pyramid.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

Pyramid::Pyramid(){
	
}

Pyramid::~Pyramid(){

}

Pyramid::Pyramid(const Pyramid & orig){

}

void Pyramid::draw(){
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(orientation);
	float red[4]   = {.5,0,0,1};
	float blue[4]  = {0,0,.5,1};
	float green[4] = {0,.5,0,1};
	float white[4] = {.5,.5,.5,1};
	float gray[4]  = {.3,.3,.3,1};

	if (selected){
		for (int i=0;i<3;i++){
			red[i]=min(red[i]*2,1);
			blue[i]=min(blue[i]*2,1);
			white[i]=min(white[i]*2,1);
			gray[i]=min(gray[0]*2,1);
		}
	}
	glBegin(GL_TRIANGLES);
	// Make the red square
	glColor4fv(red);
	glVertex3f(-.5,-.5,-.5);
	glVertex3f(.5,-.5,-.5);
	glVertex3f(-.5,-.5,.5);

	glVertex3f(.5,-.5,-.5);
	glVertex3f(-.5,-.5,.5);
	glVertex3f(.5,-.5,.5);

	// Make the bottom blue
	glColor4fv(blue);
	glVertex3f(-.5,-.5,-.5);
	glVertex3f(.5,-.5,-.5);
	glVertex3f(0,.5,0);

	// Make the front green
	glColor4fv(green);
	glVertex3f(.5,-.5,.5);
	glVertex3f(.5,-.5,-.5);
	glVertex3f(0,.5,0);

	// Make the back gray
	glColor4fv(gray);
	glVertex3f(-.5,-.5,.5);
	glVertex3f(-.5,-.5,-.5);
	glVertex3f(0,.5,0);
	
	// Make the top white 
	glColor4fv(white);
	glVertex3f(.5,-.5,.5);
	glVertex3f(-.5,-.5,.5);
	glVertex3f(0,.5,0);
	
	glEnd();

}
