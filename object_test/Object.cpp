#include "Object.h"

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

vector<Object *> objects;
Object::Object(){
	glMatrixMode(GL_MODELVIEW);
	glGetDoublev(GL_MODELVIEW_MATRIX,orientation);
	selected=false;
}

Object::~Object(){

}
void Object::print_orientation(){
	printf("orientation: ");
	for (int i=0;i<16;i++){
		printf("%f ",orientation[i]);
	}
	printf("\n");
}
Object::Object(const Object & orig){
	set_orientation(orig.orientation);
}

void Object::move_forward(double x){ translate(0,x,0);}
void Object::move_right(double x){	 translate(x,0,0);}
void Object::move_up(double x){      translate(0,0,x);}
void Object::roll_right(double x){   rotate(x,0,1,0);}
void Object::turn_up(double x){      rotate(x,1,0,0);}


// *****************************************
// Low Level Functions for object movement
// *****************************************

void Object::rotate(double angle, double x, double y, double z){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//glLoadIdentity();
	glLoadMatrixd(orientation);
	glRotated(angle,x,y,z);
	glGetDoublev(GL_MODELVIEW_MATRIX,orientation);
	glPopMatrix();
	glEnd();
}

void Object::translate(double x,double y,double z){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixd(orientation);
	glTranslated(x,y,z);
	glGetDoublev(GL_MODELVIEW_MATRIX,orientation);
	glPopMatrix();
	glEnd();
}

float Object::min(float a, float b){
	if (a<b){
		return a;
	} 
	return b;
}

void Object::draw(){
	glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	glMultMatrixd(orientation);
	float blue[4]  = {0,0,.5,1};
	
	if (selected){
		for (int i=0;i<3;i++){
			blue[i]=min(blue[i]*2,1);
		}
	}

	glColor4fv(blue);

	glutSolidCube(1.0);
	//glPopMatrix();
}
	
void Object::set_orientation(const double * new_orientation){
	memcpy(orientation,new_orientation,sizeof(double)*16);
}	


vector<double> Object::get_position(){
	vector<double> position;
	position.reserve(3);
	position.push_back(orientation[12]);
	position.push_back(orientation[13]);
	position.push_back(orientation[14]);
	return position;
}
