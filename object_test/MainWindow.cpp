#include "MainWindow.h"
#include <GL/glut.h>
#include <stdio.h>
#include <glm/glm.hpp>
#include "Object.h"
#include "Global.h"
#include <stdlib.h>
int main_window;
int sub_window_overhead;
int sub_window_player;
int main_window_width;
int main_window_height;

move_mode_t move_mode=MOVE_MODE_TRANSLATE;
int object_ind=-1;
Object * camera;
void idle(void){
	int curwin=glutGetWindow();
	glutSetWindow(main_window);
	glutPostRedisplay();
	glutSetWindow(sub_window_overhead);
	glutPostRedisplay();
	glutSetWindow(sub_window_player);
	glutPostRedisplay();
	glutSetWindow(curwin);
}

void move_current_object(int key){
	Object * obj=NULL;
	if (object_ind>=0){
		obj=objects[object_ind];
	} else {
		obj=camera;
	}
	switch(key){
	case GLUT_KEY_UP:
		if (move_mode==MOVE_MODE_TRANSLATE){
			obj->move_forward(.2);
		} else if (move_mode==MOVE_MODE_ROTATE){
			obj->turn_up(2);
		}
		break;
	case GLUT_KEY_DOWN:
		if (move_mode==MOVE_MODE_TRANSLATE){
			obj->move_forward(-.2);
		} else if (move_mode==MOVE_MODE_ROTATE){
			obj->turn_up(-2);
		}
		break;
	case GLUT_KEY_RIGHT:
		if (move_mode==MOVE_MODE_TRANSLATE){
			obj->move_right(.2);
		} else if (move_mode==MOVE_MODE_ROTATE){
			obj->roll_right(2);
		}
		break;
	case GLUT_KEY_LEFT:
		if (move_mode==MOVE_MODE_TRANSLATE){
			obj->move_right(-.2);
		} else if (move_mode==MOVE_MODE_ROTATE){
			obj->roll_right(-2);
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
}



void special_generic(int key, int x, int y){
	move_current_object(key);
}

void special_overhead_window(int key, int x, int y){
	special_generic(key,x,y);
}
void special_player_window(int key, int x, int y){
	special_generic(key,x,y);
}

void generic_keypress(unsigned char key, int x ,int y){
	switch (key){
	case 'r':
		move_mode=MOVE_MODE_ROTATE;
		break;
	case 't':
		move_mode=MOVE_MODE_TRANSLATE;
		break;
	default:
		printf("unhandled keypress: %c,%d,%d\n",key,x,y);
		break;
	}
}

void keypress_player_window(unsigned char key, int x, int y){
	generic_keypress(key, x, y);
}
void keypress_overhead_window(unsigned char key, int x, int y){
	generic_keypress(key, x, y);
	
}

void draw_objects(double * orientation){
	glMatrixMode(GL_MODELVIEW);
	double inv[16];
	for (unsigned int i=0;i<objects.size();i++){
		glLoadIdentity();
		if (orientation){
			gluInvertMatrix(orientation,inv);
			glMultMatrixd(inv);
		}
		objects[i]->draw();
	}
}


void display_main_window(void){
	// The main window doesn't really display anything because the space is covered by the subwindows
}


void display_overhead_window(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(90.0, // field of view in degrees
								 1.0,  // aspect ratio
								 1.0,  // Z near
								 50     // Z far
								 );
	gluLookAt(0.0, 0.0, 10, // x,y,z eye location
						0.0, 0.0, 0.0, // location to look at
						1.0, 0.0, 0.0); // "up" vector
	draw_objects();
	glutSwapBuffers();
	
}

void display_player_window(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(90.0, // field of view in degrees
								 1.0,  // aspect ratio
								 1.0,  // Z near
								 50     // Z far
								 );
	gluLookAt(0.0, -10.0, 0, // x,y,z eye location
						0.0, 0.0, 0.0, // location to look at
						0.0, 0.0, 1.0); // "up" vector
	draw_objects(camera->orientation);
	glutSwapBuffers();
}
void generic_mouse_click(int button, int state, int x, int y){
	float depth;
	if (button!=0 || state!=0){
		return;
	}
	glReadPixels(x,main_window_height-y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT, & depth);
	//printf("overhead_window mouse: %d,%d,%d,%d,%f\n",button,state,x,y,depth);
	vector<double> realxyz=screen_to_world(x,y,depth);
	//printf("real x,y,z:%f,%f,%f\n",realxyz[0],realxyz[1],realxyz[2]);
	
	double min_dist=100;
	int min_ind=-1;

		
	for (unsigned int i=0;i<objects.size();i++){
		double dist=0;
		vector<double> position=objects[i]->get_position();

		for (int j=0;j<3;j++){
			dist+=(realxyz[j]-position[j])*(realxyz[j]-position[j]);
		}

		if (dist<min_dist){
			min_dist=dist;
			min_ind=i;
		}
	}
	object_ind=min_ind;
	for (unsigned int i=0;i<objects.size();i++){
		if ((int)i==min_ind){
			objects[i]->selected=true;
		} else {
			objects[i]->selected=false;
		}
	}
}


void mouse_overhead_window(int button, int state, int x, int y){
	int curwin=glutGetWindow();
	glutSetWindow(sub_window_overhead);
	generic_mouse_click(button,state,x,y);
	glutSetWindow(curwin);
}
void mouse_player_window(int button, int state, int x ,int y){
	int curwin=glutGetWindow();
	glutSetWindow(sub_window_player);
	generic_mouse_click(button,state,x,y);
	glutSetWindow(curwin);
}

void init_overhead_window(){
	// Create overhead viewing window
	
	sub_window_overhead=glutCreateSubWindow(main_window,0,0,main_window_width/2,main_window_height);
	glEnable(GL_DEPTH_TEST);
	
	glutKeyboardFunc(keypress_overhead_window);
	glutDisplayFunc(display_overhead_window);
	glutMouseFunc(mouse_overhead_window);
	glutSpecialFunc(special_overhead_window);
	
	glMatrixMode(GL_PROJECTION);
	gluPerspective(50.0, // field of view in degrees
								 1.0,  // aspect ratio
								 1.0,  // Z near
								 50     // Z far
								 );
	gluLookAt(0.0, 0.0, 2, // x,y,z eye location
						0.0, 0.0, 0.0, // location to look at
						0.0, 1.0, 0.0); // "up" vector

}

void init_player_window(){
	glViewport(main_window_width/2,0,main_window_width/2,main_window_height);

	sub_window_player=glutCreateSubWindow(main_window,main_window_width/2,0,main_window_width/2,main_window_height);
	glEnable(GL_DEPTH_TEST);
	
	glutKeyboardFunc(keypress_player_window);
	glutDisplayFunc(display_player_window);
	glutMouseFunc(mouse_player_window);
	glutSpecialFunc(special_player_window);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(50.0, // field of view in degrees
								 1.0,  // aspect ratio
								 1.0,  // Z near
								 50     // Z far
								 );
	gluLookAt(0.0, 0.0, 2.0, // x,y,z eye location
						0.0, 0.0, 0.0, // location to look at
						0.0, 1.0, 0.0); // "up" vector


}
void init_main_window(){
	// Create Main Window
	main_window_width=1000;
	main_window_height=500;
	main_window=glutCreateWindow("graphics_test");
	glutReshapeWindow(main_window_width,main_window_height);
	glutDisplayFunc(display_main_window);
	glutSpecialFunc(special_player_window);
	//sub_window_player=glutCreateSubWindow(main_window,main_window_width/2,0,main_window_width/2,main_window_height);
	camera=new Object();
	init_overhead_window();
	init_player_window();
	glLoadIdentity();
	
	
}

