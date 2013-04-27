#include "Global.h"
#include <GL/glut.h>

vector<double> screen_to_world(int x, int y, float depth){
	vector<double> realxyz;

	// Initialize output vector
	realxyz.clear();
	realxyz.reserve(3);
	for (int i=0;i<3;i++){
		realxyz.push_back(0);
	}
	glLoadIdentity();
	// Get the GL state
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT,viewport);
	double modelview[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	double projection[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	// Perform the "unprojection"
	gluUnProject(x,main_window_height-y,depth,modelview,projection,viewport,&realxyz[0],&realxyz[1],&realxyz[2]);
	realxyz[0]=realxyz[0];
	realxyz[1]=realxyz[1];
	realxyz[2]=realxyz[2];
	return realxyz;


}
