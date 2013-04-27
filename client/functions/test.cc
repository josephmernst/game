#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159
#define PI_2 1.57079

#include "geometry.h"

int main(int argc, char **argv){
  float x[3] = {1, 0, 0};
  
  float axis[3] = {0, 1, 0};
  
  float **R;
  R = compute_rotate(axis, PI_2);
  printf("R=\n");
  print(R, 3, 3);
  
  float *y;
  y = matrix_mult(R, x, 3);
  //print(y, 3);
  
  float *z;
  z = matrix_add(x, y, 3);
  printf("x=\n");
  print(x, 3);
  printf("y=\n");
  print(y, 3);
  printf("z=\n");
  print(z, 3);
  
  
}
