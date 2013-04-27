#include <stdio.h>
#include <stdlib.h>
#include <GL/glfw.h>
#include <math.h>
#include <string.h>
#include "functions/geometry.h"
#include "flyingObject.h"
 
void Init(void);
void Shut_Down(int return_code);
void Main_Loop(void);
void Draw_Square(float red, float green, float blue);
void Draw(void);
 
float rotate_y = 0,
      rotate_x = 0,
      rotate_z = 0;
const float rotations_per_tick = .2;
const int window_width = 800,
  window_height = 600;

float view_x = 0,
  view_y = 0,
  view_z = 0;
float trans_x = 0,
  trans_y = 0,
  trans_z = 0;

float location[3];

flyingObject view;

int main(void)
{
  Init();
  Main_Loop();
  Shut_Down(0);
}
 
void Init(void)
{
  if (glfwInit() != GL_TRUE)
    Shut_Down(1);
  // 800 x 600, 16 bit color, no depth, alpha or stencil buffers, windowed
  if (glfwOpenWindow(window_width, window_height, 5, 6, 5,
                     0, 0, 0, GLFW_WINDOW) != GL_TRUE)
    Shut_Down(1);
  glfwSetWindowTitle("game client");
 
  // set the projection matrix to a normal frustum with a max depth of 50
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float aspect_ratio = ((float)window_height) / window_width;
  glFrustum(0.5, -0.5, -0.5 * aspect_ratio, 0.5 * aspect_ratio, 1, 1000);
  glMatrixMode(GL_MODELVIEW);
  
  //check that there's a joystick
  if(glfwGetJoystickParam(GLFW_JOYSTICK_1, GLFW_PRESENT) == GL_FALSE)
    Shut_Down(1);
}
 
void Shut_Down(int return_code)
{
  glfwTerminate();
  exit(return_code);
}
 
void Main_Loop(void)
{
  float joy_position[6];
  unsigned char buttons[16];
  
  // the time of the previous frame
  double old_time = glfwGetTime();
  // this just loops as long as the program runs
  while(1)
  {
    float radius;
    
    // calculate time elapsed, and the amount by which stuff rotates
    double current_time = glfwGetTime(),
           delta_rotate = (current_time - old_time) * rotations_per_tick * 360;
    old_time = current_time;
    // escape to quit, arrow keys to rotate view
    if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
      break;
    if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
      rotate_y += delta_rotate;
    if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
      rotate_y -= delta_rotate;
    // z axis always rotates
    rotate_z += delta_rotate;
    
    glfwGetJoystickPos(GLFW_JOYSTICK_1, joy_position, 6);
    rotate_y += delta_rotate*joy_position[0];
    rotate_x += delta_rotate*joy_position[1];
    
    view_x += delta_rotate*joy_position[3];
    view_y += delta_rotate*joy_position[2];
    
    glfwGetJoystickButtons(GLFW_JOYSTICK_1, buttons, 16);
    radius = delta_rotate*buttons[0] - delta_rotate*buttons[1];
    trans_z += radius;
    
    float position[3];
    
    
    float axis[3];
    axis[0] = rotate_x;
    axis[1] = rotate_y;
    axis[2] = rotate_z;
    view.setOrientation(axis);
    
    if(buttons[2]){
      printf("firing lasers\n");
    }
    
    // clear the buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    
    // draw the figure
    Draw();
    
    // swap back and front buffers
    glfwSwapBuffers();
  }
}
 
void Draw_Square(float red, float green, float blue)
{
  // Draws a square with a gradient color at coordinates 0, 10
  glBegin(GL_QUADS);
  {
    glColor3f(red, green, blue);
    glVertex2i(1, 11);
    glColor3f(red * .8, green * .8, blue * .8);
    glVertex2i(-1, 11);
    glColor3f(red * .5, green * .5, blue * .5);
    glVertex2i(-1, 9);
    glColor3f(red * .8, green * .8, blue * .8);
    glVertex2i(1, 9);
  }
  glEnd();
}
 
void Draw(void)
{ 
  // reset view matrix
  glLoadIdentity();
  
  glRotatef(view_x, 1, 0, 0);
  glRotatef(view_y, 0, 1, 0);
  glRotatef(view_z, 0, 0, 1);
  
  glTranslatef(trans_x, trans_y, -30+trans_z);
  
  //printf("views: %f\t%f\t%f\n", view_x, view_y, view_z);
  printf("position = %f\t%f\t%f\n", location[0], location[1], location[2]);
  
  // apply the current rotation
  glRotatef(rotate_x, 1, 0, 0);
  glRotatef(rotate_y, 0, 1, 0);
  glRotatef(rotate_z, 0, 0, 1);
  // by repeatedly rotating the view matrix during drawing, the
  // squares end up in a circle
  int i = 0, squares = 15;
  float red = 0, blue = 1;
  for (; i < squares; ++i){
    glRotatef(360.0/squares, 0, 0, 1);
    // colors change for each square
    red += 1.0/12;
    blue -= 1.0/12;
    Draw_Square(red, .6, blue);
  }
}
