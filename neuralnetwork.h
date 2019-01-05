#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrice.h"

struct neural_network
{
    matrix imput;
    matrix w_imput_to_hidden;
    matrix hidden;
    matrix w_hidden_to_output;
    matrix output;
    matrix bias_imput_to_hidden;
    matrix bias_hidden_to_output;
};
typedef struct neural_network net;
void free_mat(matrix* a);
net create_a_network(int imp, int hid, int out);
void free_n_n(net* a);
void init_first_feedforward(net *a, float **value,int j);
void feedforward(net* a, matrix w_i_h, matrix w_h_o);
void backpropagation(net* a, int *label, int j);
