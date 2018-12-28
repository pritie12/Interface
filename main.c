# include <stdio.h>
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
# include <err.h>
# include <math.h>
#include "mysdl.h"
#include "interface.h"




//# include "image_processing.h"


/* I) Fenètre d'acceuile
 *      -train
 *      -test
 *        >image
 *        >draw
 * 
 * fenetre/ bouton /le draw*/



/*SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;
    img = IMG_Load(path);
    return img;
}*/


int main(int argc, char *argv[])
{

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Surface *img = load_image(argv[1]);
    open_image(img);
    wait_for_keypressed();
    
    SDL_FreeSurface(img);
    
    //fenetre 1
    
    SDL_Surface *ecran=NULL ;
    
   
    
    //initialisation ecran
    ecran = SDL_SetVideoMode ( 500 ,500 ,32 , SDL_HWSURFACE | SDL_DOUBLEBUF );
    
    SDL_FillRect( ecran, NULL,SDL_MapRGB(ecran->format,0,0,0));
    SDL_Flip(ecran);
    
   /*  SDL_Surface *draw = load_image("draw.png");
     SDL_Rect position;
     
     position.x=20;
     position.y=20;
     
    SDL_BlitSurface(draw,NULL, ecran, &position);
    
    SDL_Flip(ecran);*/
    //wait_for_keypressed();

    //wait_for_draw(draw,ecran);
   /* position.x=200;
    position.y=200;
    
    
    SDL_BlitSurface(draw,NULL, ecran, &position);*/
    
    SDL_Flip(ecran);
    
    
    
    //mise en place des boutons
    
    fenetre_1(ecran);
    
    
    
    SDL_Flip(ecran);
    
    wait_for_keypressed();
  //  SDL_FreeSurface(draw);
    

    

     

   
    //fenetre_test();
    
    
    TTF_Quit();
    
    SDL_Quit();
   //argv[1] = 'a';
    return argc;
    
}



