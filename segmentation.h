#ifndef SEGMENTATION_H
# define SEGMENTATION_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include <math.h>
#include "mysdl.h"
#include "nn.h"

void horizontal(SDL_Surface *img);
int vertical(SDL_Surface *img, int starter , int ending);
int separate(SDL_Surface *img);
void grayscale(SDL_Surface *img);
void blacknwhite(SDL_Surface *img);
void resize (SDL_Surface *scr ,int **src_bin, int (*dest)[28]);
void binarised(SDL_Surface *img, float *tab);
void new_image(SDL_Surface *img, int *result);


#endif /* !SEGMENTATION_H */
