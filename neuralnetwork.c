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

void free_mat(matrix* a)
{
    for (int i = 0; i < a->rows; i++)
        free(a->mat[i]);
    free(a->mat);
}

net create_a_network(int imp, int hid, int out)
{
    net a =
    {
        create_a_matrix(imp, 1),
        create_a_matrix(hid,imp),
        create_a_matrix(hid,1),
        create_a_matrix(out,hid),
        create_a_matrix(out,1),
        create_a_matrix(hid, 1),
        create_a_matrix(out,1)
    };
    return a;
}

void free_n_n(net* a)
{
    free_mat(&a->imput);
    free_mat(&a->w_imput_to_hidden);
    free_mat(&a->hidden);
    free_mat(&a->w_hidden_to_output);
    free_mat(&a->output);
    free_mat(&a->bias_imput_to_hidden);
    free_mat(&a->bias_hidden_to_output);
}

void feedforward(net* a, matrix w_i_h, matrix w_h_o)
{
    //dans main faire create_a_network(,,);feedforward(net a,n) init n = 0 aussi
    //mettre les imputs dans la matrice imputs du nn à partir de train.pixel[n][]
    //il faut ajuster la fonction rand pour que les valeurs soient entre -1 et 1
    // a.w_imput_to_hidden = set_random_matrix(a.w_imput_to_hidden.rows,a.w_imput_to_hidden.columns);
    //a.bias_imput_to_hidden = set_random_matrix(a.bias_imput_to_hidden.rows,a.bias_imput_to_hidden.columns);

    //WEIGHT I to H
    a->w_imput_to_hidden = w_i_h;

    //WEIGHT H to O
    a->w_hidden_to_output = w_h_o;

    //IMPUT TO HIDDEN
    matrix t = multiply(a->w_imput_to_hidden, a->imput);
    matrix b = add(t, a->bias_imput_to_hidden);
    free_mat(&t);
    a->hidden = sigmoid(b);

    // a.w_hidden_to_output = set_random_matrix(a.w_hidden_to_output.rows, a.w_hidden_to_output.columns);
    //a.bias_hidden_to_output = set_random_matrix(a.bias_hidden_to_output.rows, a.bias_hidden_to_output.columns);

    //HIDDEN TO OUTPUT
    matrix h = multiply(a->w_hidden_to_output, a->hidden);
    matrix g = add(h, a->bias_hidden_to_output);
    free_mat(&h);
    a->output = sigmoid(g);
}

void init_first_feedforward(net* a, float **value, int j)
{
    for (int i = 0; i < a->imput.rows; i++)
    {
        a->imput.mat[i][0] = value[j][i];
    }
    if( j == 0)
    {
        //a->w_imput_to_hidden = set_random_matrix(a->w_imput_to_hidden.rows, a->w_imput_to_hidden.columns);
        a->bias_imput_to_hidden = set_random_matrix(a->bias_imput_to_hidden.rows, a->bias_imput_to_hidden.columns);
       // a->w_hidden_to_output = set_random_matrix(a->w_hidden_to_output.rows, a->w_hidden_to_output.columns);
        a->bias_hidden_to_output = set_random_matrix(a->bias_hidden_to_output.rows, a->bias_hidden_to_output.columns);
    }
}
void backpropagation(net* a, int *label, int j)
{
    float learningrate = 0.2;
    matrix target = target_int_to_matrix(label[j], a->output.rows);
    //int r = max(target);
    int z = 0;
    while (z < 250)
    {

        //error_output = target - output
        matrix error_output = substract(target, a->output);
        //transpose w_h_to_o
        matrix tw_h_o = transpose(a->w_hidden_to_output);
        //error_hidden = tw_h_o*e
        matrix error_hidden = multiply(tw_h_o, error_output);
        //deltaw_h_o = lr * error_output * (output * (1 - output) * trans(hidden)
        matrix f = grad(a->output);
        matrix c = multiply_weird(error_output, f);
        matrix thidden = transpose(a->hidden);
        matrix deltabiasw_h_o = multiply_scalar(learningrate,c);
        matrix deltaw_h_o = multiply(deltabiasw_h_o, thidden);
        //deltaw_i_h = lr * error_hidden * (hidden * (1 - hidden) * trans(imput)
        matrix g = grad(a->hidden);
        matrix k = multiply_weird(error_hidden, g);
        matrix timput = transpose(a->imput);
        matrix deltabias_i_h = multiply_scalar(learningrate,k);
        matrix deltaw_i_h = multiply(deltabias_i_h, timput);
        //new weights/bias
        matrix new_w_o = add(a->w_hidden_to_output, deltaw_h_o);
        //free_mat(&a->w_hidden_to_output);
        a->w_hidden_to_output = new_w_o;
        matrix new_b_o = add(a->bias_hidden_to_output, deltabiasw_h_o);
        //free_mat(&a->bias_hidden_to_output);
        a->bias_hidden_to_output = new_b_o;
        matrix new_w_i = add(a->w_imput_to_hidden, deltaw_i_h);
        //free_mat(&a->w_imput_to_hidden);
        a->w_imput_to_hidden = new_w_i;
        matrix new_b_i = add(a->bias_imput_to_hidden, deltabias_i_h);
        //free_mat(&a->bias_imput_to_hidden);
        a->bias_imput_to_hidden = new_b_i;

        feedforward(a, a->w_imput_to_hidden, a->w_hidden_to_output);
        //z =  pourcent(a->output, r);
        z++;

        //FREE
        free_mat(&error_output);
        free_mat(&tw_h_o);
        free_mat(&error_hidden);
        free_mat(&f);
        free_mat(&c);
        free_mat(&thidden);
        free_mat(&deltabiasw_h_o);
        free_mat(&deltaw_h_o);
        free_mat(&g);
        free_mat(&k);
        free_mat(&timput);
        free_mat(&deltabias_i_h);
        free_mat(&deltaw_i_h);
    }
    free_mat(&target);
}
