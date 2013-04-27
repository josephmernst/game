void norm(float *x, int x_length);
void print(float *x, int x_length);
void print(float **x, int n, int m);
float** matrix_mult(float **a, float **b, int n, int m, int l);
float* matrix_mult(float **a, float *b, int n);
float** matrix_add(float **a, float **b, int n, int m);
float* matrix_add(float *a, float *b, int n);
float **compute_rotate(float *axis, float theta);
void scale(float* x, float x_length, float a);
