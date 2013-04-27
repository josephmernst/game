#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flyingObject.h"

int main(int argc, char **argv){
  flyingObject view;
  //view = new flyingObject;
  float x[3];
  
  //x = (float*)malloc(3*sizeof(float));
  for(int i = 0; i < 3; i++){
    x[i] = i;
    //printf("x[%d] = %f\n", i, x[i]);
  }
  
  view.setPosition(x);
  view.setOrientation(x);
  view.setVelocity(x);
  view.setAcceleration(x);
  view.print();
  
  return 0;
}
