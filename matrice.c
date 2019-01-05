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

matrix create_a_matrix(int rows, int columns)
{
    matrix m  = {rows, columns, calloc(rows * columns, sizeof(float*))};
    for (int i =0; i < rows; i++)
    {
        m.mat[i] = calloc(columns, sizeof(m.mat[i][0]));
    }
    return m;
}

matrix ask_value(matrix m)
{
    float a;
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {
            scanf("%f", &a);
            m.mat[i][j] = a;
        }
    }
    return m;
}

matrix init(matrix m)
{
    for(int i = 0; i < m.rows; i++)
    {
        for(int j = 0; j < m.columns; j++)
        {
            m.mat[i][j] = 0;
        }
    }
    return m;
}

matrix set_random_matrix(int rows, int columns)
{
    srand(time(NULL));
    matrix res = create_a_matrix(rows, columns);
    for(int i = 0; i < res.rows; i++)
    {
        for(int j = 0; j < res.columns; j++)
        {
            int x = rand();
            if(x % 2 == 0)
                res.mat[i][j] = -(float)rand() / (float)RAND_MAX;
            else
            {
                res.mat[i][j] = (float)rand() /(float) RAND_MAX;
            }
        }
    }
    return res;
}

void print_a_matrix(matrix m)
{
    for(int i = 0; i < m.rows; i++)
    {
        for(int j = 0; j < m.columns; j++)
        {
            printf("%f ", (m.mat[i][j]));
        }
        printf("\n");
    }
}

matrix add(matrix a, matrix b)
{
    assert(a.rows == b.rows);
    assert(a.columns == b.columns);
    matrix res = create_a_matrix(a.rows,a.columns);
    for(int i = 0; i < a.rows; i++)
    {
        for(int j = 0; j < a.columns; j++)
        {
            res.mat[i][j] = a.mat[i][j] + b.mat[i][j];
        }
    }
    return res;
}

matrix substract(matrix a, matrix b)
{
    assert(a.rows == b.rows);
    assert(a.columns == b.columns);
    matrix res = create_a_matrix(a.rows, a.columns);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.columns; j++)
        {
            res.mat[i][j] = a.mat[i][j] - b.mat[i][j];
        }
    }
    return res;
}

matrix grad(matrix a)
{
    matrix res = create_a_matrix(a.rows, a.columns);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.columns; j++)
        {
            res.mat[i][j] = a.mat[i][j] * (1 - a.mat[i][j]);
        }
    }
    return res;
}

matrix multiply_weird(matrix a, matrix b)
{
    assert(a.rows == b.rows);
    assert(a.columns == b.columns);
    matrix res = create_a_matrix (a.rows, a.columns);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.columns; j++)
        {
            res.mat[i][j] = a.mat[i][j] * b.mat[i][j];
        }
    }
    return res;
}

matrix multiply_scalar(float a, matrix b)
{
    matrix res = create_a_matrix(b.rows,b.columns);
    for(int i = 0; i < b.rows; i++)
    {
        for(int j = 0; j < b.columns; j++)
        {
            res.mat[i][j] = a * b.mat[i][j];
        }
    }
    return res;
}

matrix multiply(matrix a, matrix b)
{
    assert(a.columns == b.rows);
    int p = a.columns;
    matrix res = create_a_matrix(a.rows,b.columns);
    res = init(res);
    for(int i = 0; i < a.rows; i++)
    {
        for(int j = 0; j < b.columns; j++)
        {
            for(int k = 0; k < p; k++)
            {
                res.mat[i][j] += a.mat[i][k] * b.mat[k][j];
            }
        }
    }
    return res;
}

matrix transpose(matrix a)
{
    matrix res = create_a_matrix(a.columns, a.rows);
    res = init(res);
    for(int i = 0; i < res.rows; i++)
    {
        for(int j = 0; j < res.columns; j++)
        {
            res.mat[i][j] = a.mat[j][i];
        }
    }
    return res;
}

matrix sigmoid(matrix a)
{
    for(int i = 0; i < a.rows; i++)
    {
        for(int j = 0; j < a.columns; j++)
        {
            a.mat[i][j] = (1 / (1 + exp(-a.mat[i][j])));
        }
    }
    return a;
}

matrix target_int_to_matrix(int a, int rows)
{
    assert( a < rows);
    matrix res = create_a_matrix(rows,1);
    for (int i = 0; i < rows; i++)
    {
        if( i == a )
        {
            res.mat[i][0] = 1;
        }
        else
        {
            res.mat[i][0] = 0;
        }
    }
    return res;
}

int max(matrix a)
{
    int m = 0;
    int c = 0;
    for(int i = 0; i < a.rows; i++)
    {
        for(int j = 0; j < a.columns; j++)
        {
            if(a.mat[i][j] > m)
            {
                m = a.mat[i][j];
                c = 0;
                c = i;
            }
        }
    }
    return c;
}

int equal(matrix a, matrix b)
{
    assert(a.rows == b.rows);
    assert(a.columns == b.columns);
    int c = max(a);
    int r = max(b);
    if (c == r)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int pourcent(matrix a, int r)
{
    assert(a.rows > r);
    float sum = 0;
    for(int i = 0; i < a.rows; i++)
    {
        if(i != r)
        {
            float b = a.mat[i][0];
            sum = sum + b;
        }
    }
    if( sum < 0.07)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*void free_a_matrix(matrix m)
  {
  free(m);
  }*/
