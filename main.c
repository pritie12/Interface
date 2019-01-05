#include "main.h"
int in = 28 *28;
int hid = 16;
int out = 10;
net *a;




void run_image_treatment(char *img)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Surface *img_surface = load_image(img);
    open_image(img_surface);
    wait_for_keypressed();

    /*grayscale(img);
      open_image(img);
      wait_for_keypressed();
      blacknwhite(img);
      open_image(img);
      wait_for_keypressed();
      horizontal(img);
      open_image(img);
      wait_for_keypressed();
      separate(img);
      open_image(img);
      wait_for_keypressed();
      resize(img);
      wait_for_keypressed();
      open_image(img);
      wait_for_keypressed();*/

    SDL_FreeSurface(img_surface);
    SDL_Quit();
}


int main(int argc, char *argv[])
{
    run_image_treatment(argv[1]);
    srand(time(NULL));
    //data preparation train
    /*float **train = calloc(60000, sizeof(float *));
      for (int i = 0; i < 60000; i++)
      {
      train[i] = calloc(784, sizeof(float));
      }
      int *label_train = calloc(60000, sizeof(int));
      put_train_value_in_array(train, label_train);*/

    //MENU
    a = init_neural_network(in, hid, out);
    put_weights_in_arrays(a -> w_input_to_hidden, in, hid, "wIH.txt");
    put_weights_in_arrays(a -> w_hidden_to_output, hid, out, "wHO.txt");
    put_biases_in_arrays(a -> bias_input_to_hidden, hid, "bIH.txt");
    put_biases_in_arrays(a -> bias_hidden_to_output, out, "bHO.txt");



    //TRAINING
    /*int epoch = 1000;
      run_neural_network(a, train, label_train, epoch);
      printf("TRAINED!\n");
      print_weights(a -> w_input_to_hidden, a -> w_hidden_to_output,in, hid, out);
      print_biases(a -> bias_input_to_hidden, a -> bias_hidden_to_output, hid, out);*/

    //INTERFACE
    SDL_Surface *ecran = NULL;
    ecran = SDL_SetVideoMode(500, 500, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran -> format, 0, 0, 0));
    SDL_Flip(ecran);
    wait_for_keypressed();
    fenetre_1(ecran);
    wait_for_keypressed();
    TTF_Quit();
    SDL_Quit();

    //data preparation test
    /*int *label_test = calloc(10000, sizeof(float));
      float **test = calloc(10000, sizeof(float*));
      for (int i = 0; i < 10000; i++)
      {
      test[i] = calloc(784, sizeof(float));
      }
      put_test_value_in_array(test, label_test);
      free(label_test);
      put_weights_in_arrays(a -> w_input_to_hidden, in, hid, "wIH.txt");
      put_weights_in_arrays(a -> w_hidden_to_output, hid, out, "wHO.txt");
      put_biases_in_arrays(a -> bias_input_to_hidden, hid, "bIH.txt");
      put_biases_in_arrays(a -> bias_hidden_to_output, out, "bHO.txt");

    //TESTING
    int m ;
    for (int j = 0; j < 100; j++)
    {
    m = 0;
    for (int i = 0; i < a -> nbr_input; i++)
    {
    a -> input[i] = 0;
    a -> input[i] = test[j][i];
    }
    feedforward(a);
    for (int i = 0; i < a -> nbr_output; i++)
    {
    printf("%f", a -> output[i]);
    }
    m = max_array( a -> output, a -> nbr_output);
    printf(" %d\n", m);
    m = 0;
    }*/

    /*free_test(test);
    free_train(train);
    free(label_train);*/

    return argc;
}
