#include "flyingObject.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void check_vec(float* x){
  if(sizeof(x)/sizeof(float) != 3){
    printf("The input vector didn't have 3 components.\n");
    printf("  sizeof(x) = %d\n", (int)sizeof(x));
    printf("  sizeof(float) = %d\n", (int)sizeof(float));
    exit(1);
  }
}


//No argument constructor
flyingObject::flyingObject(){
  position = (float*)malloc(3*sizeof(float));
  velocity = (float*)malloc(3*sizeof(float));
  acceleration = (float*)malloc(3*sizeof(float));
  orientation = (float*)malloc(3*sizeof(float));
  
  //Give the parameters default values
  for(int i = 0; i < 3; i++){
    position[i] = 0;
    orientation[i] = 0;
    velocity[i] = 0;
    acceleration[i] = 0;
  }
}

//Constructor with position defined
flyingObject::flyingObject(float* s){
  position = (float*)malloc(3*sizeof(float));
  velocity = (float*)malloc(3*sizeof(float));
  acceleration = (float*)malloc(3*sizeof(float));
  orientation = (float*)malloc(3*sizeof(float));
  
  check_vec(s);
  memcpy(position, s, sizeof(s));
  
  //Give the other parameters default values
  for(int i = 0; i < 3; i++){
    orientation[i] = 0;
    velocity[i] = 0;
    acceleration[i] = 0;
  }
}

//Constructor with position and orientation defined
flyingObject::flyingObject(float* s, float *axis){
  position = (float*)malloc(3*sizeof(float));
  velocity = (float*)malloc(3*sizeof(float));
  acceleration = (float*)malloc(3*sizeof(float));
  orientation = (float*)malloc(3*sizeof(float));
  
  check_vec(s);
  memcpy(position, s, sizeof(s));
  
  check_vec(axis);
  memcpy(orientation, axis, sizeof(axis));
  
  //Give the other parameters default values
  for(int i = 0; i < 3; i++){
    velocity[i] = 0;
    acceleration[i] = 0;
  }
}

//Constructor with position, orientation, and velocity defined
flyingObject::flyingObject(float* s, float* axis, float* v){
  position = (float*)malloc(3*sizeof(float));
  velocity = (float*)malloc(3*sizeof(float));
  acceleration = (float*)malloc(3*sizeof(float));
  orientation = (float*)malloc(3*sizeof(float));
  
  check_vec(s);
  memcpy(position, s, sizeof(s));
  
  check_vec(axis);
  memcpy(orientation, axis, sizeof(axis));
  
  check_vec(v);
  memcpy(velocity, v, sizeof(v));
  
  //Give the other parameter default values
  for(int i = 0; i < 3; i++){
    acceleration[i] = 0;
  }
}

//Constructor with position, orientation, velocity, and acceleration defined
flyingObject::flyingObject(float* s, float* axis, float* v, float* a){
  position = (float*)malloc(3*sizeof(float));
  velocity = (float*)malloc(3*sizeof(float));
  acceleration = (float*)malloc(3*sizeof(float));
  orientation = (float*)malloc(3*sizeof(float));
  
  check_vec(s);
  memcpy(position, s, sizeof(s));
  
  check_vec(axis);
  memcpy(orientation, axis, sizeof(axis));
  
  check_vec(v);
  memcpy(velocity, v, sizeof(v));
  
  check_vec(a);
  memcpy(acceleration, a, sizeof(a));
}

flyingObject::~flyingObject(){
  free(position);
  free(velocity);
  free(acceleration);
  free(orientation);
}

void flyingObject::setPosition(float* s){
  check_vec(s);
  
  memcpy(position, s, 4*sizeof(float));
}

void flyingObject::setOrientation(float* axis){
  check_vec(axis);
  
  memcpy(orientation, axis, 4*sizeof(float));
}

void flyingObject::setVelocity(float* v){
  check_vec(v);
  
  memcpy(velocity, v, 4*sizeof(float));
}

void flyingObject::setAcceleration(float* a){
  check_vec(a);
  
  memcpy(acceleration, a, 4*sizeof(float));
}

void flyingObject::print(void){
  printf("position:     %f %f %f\n", position[0], position[1], position[2]);
  printf("orientation:  %f %f %f\n", orientation[0], orientation[1], orientation[2]);
  printf("velocity:     %f %f %f\n", velocity[0], velocity[1], velocity[2]);
  printf("acceleration: %f %f %f\n", acceleration[0], acceleration[1], acceleration[2]);
}
