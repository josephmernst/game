#include "geometry.h"

void norm(float *x, int x_length){
  float x_norm = 0;
  
  for(int i = 0; i < x_length; i++){
    x_norm += x[i]*x[i];
  }
  x_norm = sqrt(x_norm);
  
  for(int i = 0; i < x_length; i++)
    x[i] = x[i]/x_norm;
}

//Vector
void print(float *x, int x_length){
  for(int i = 0; i < x_length; i++)
    printf("%f\n", x[i]);
}

//Matrix
void print(float **x, int n, int m){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      printf("%f ", x[i][j]);
    }
    printf("\n");
  }
}

/*
  Multiply 2 matrices: a (n x m), and b (m x l)
  output: c (n x l)
*/
float** matrix_mult(float **a, float **b, int n, int m, int l){
  float **c;
  c = (float**)malloc(n*sizeof(float*));
  for(int i = 0; i < n; i++)
    c[i] = (float*)malloc(l*sizeof(float));
  
  for(int i = 0; i < n; i++){
    for(int j = 0; j < l; j++){
      c[i][j] = 0;
      
      for(int k = 0; k < m; k++)
	c[i][j] += a[i][k]*b[k][j];
      
    }
  }
  return c;
}

/*
  Multiply a matrix (n x n) by a vector (n x 1)
  output: c (n x 1)
*/
float* matrix_mult(float **a, float *b, int n){
  float *c;
  c = (float*)malloc(n*sizeof(float));
  
  for(int i = 0; i < n; i++){
    c[i] = 0;
    for(int k = 0; k < n; k++){
	c[i] += a[i][k]*b[k];
    }
  }
  return c;
}

float** matrix_add(float **a, float **b, int n, int m){
  float **c;
  c = (float**)malloc(n*sizeof(float*));
  for(int i = 0; i < n; i++){
    c[i] = (float*)malloc(m*sizeof(float));
  }
  
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      c[i][j] = a[i][j] + b[i][j];
    }
  }
  
  return c;
}

float* matrix_add(float *a, float *b, int n){
  float *c;
  
  c = (float*)malloc(n*sizeof(float));
  for(int i = 0; i < n; i++)
    c[i] = a[i] + b[i];
  
  return c;
}

//Compute a rotation matrix (assumed 3 dimensions)
float **compute_rotate(float *axis, float theta){
  float **R;
  R = (float**)malloc(3*sizeof(float*));
  for(int i = 0; i < 3; i++)
    R[i] = (float*)malloc(3*sizeof(float));
  
  float u, v, w, u2, v2, w2, c, s;
  
  norm(axis, 3);
  
  u = axis[0];
  v = axis[1];
  w = axis[2];
  u2 = u*u;
  v2 = v*v;
  w2 = w*w;
  
  c = cos(theta);
  s = sin(theta);
  
  R[0][0] =  u2 + (v2 + w2)*c;
  R[0][1] = u*v*(1-c) - w*s;
  R[0][2] = u*w*(1-c) + v*s;
  R[1][0] = u*v*(1-c) + w*s;
  R[1][1] = v2 + (u2+w2)*c;
  R[1][2] = v*w*(1-c) - u*s;
  R[2][0] = u*w*(1-c) - v*s;
  R[2][1] = v*w*(1-c)+u*s;
  R[2][2] = w2 + (u2+v2)*c;
  
  return R;
}

void scale(float* x, float x_length, float a){
  for(int i = 0; i < x_length; i++){
    x[i] *= a;
  }
}
