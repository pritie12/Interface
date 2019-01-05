#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <time.h>

struct matrix
{
  int rows;
  int columns;
  float** mat;
};

typedef struct matrix matrix;

matrix create_a_matrix(int rows, int columns);
matrix ask_value(matrix m);
matrix init(matrix m);
matrix set_random_matrix(int rows, int columns);
void print_a_matrix(matrix m);
matrix add(matrix a, matrix b);
matrix substract(matrix a, matrix b);
matrix grad(matrix a);
matrix multiply_scalar(float a, matrix b);
matrix multiply_weird(matrix a, matrix b);
matrix multiply(matrix a, matrix b);
matrix transpose(matrix a);
matrix sigmoid(matrix a);
int max(matrix a);
matrix target_int_to_matrix(int a, int rows);
int equal(matrix a, matrix b);
int pourcent(matrix a, int r);
