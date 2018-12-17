#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;
    img = IMG_Load(path);
    return img;
}


int main(int argc, char *argv[])
{

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface *img = load_image(argv[1]);
    
    SDL_FreeSurface(img);
    SDL_Quit();
    //*argv[1] = 'a';
    return argc;
    
}
