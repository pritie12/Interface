
# include <stdio.h>
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include "mysdl.h"


struct bouton
{
    SDL_Surface *surf;
     int hauteur;
    int largeur;
    SDL_Rect position;
    
};
typedef struct bouton bouton;




void fenetre_test(SDL_Surface *ecran){
    
    struct bouton *choix1=malloc(sizeof(bouton)) , *choix2=malloc(sizeof(bouton));
    
    choix1->surf=NULL;
    choix2->surf=NULL;
    
    choix1->hauteur=300;
    choix2->hauteur=choix1->hauteur;
    
    choix1->largeur=200;
    choix2->largeur= choix1->largeur;
    
    choix1->position.x=35;
    choix1->position.y=140;
    
    choix2->position.x = choix1->position.x + choix1->largeur + 30 ;
    choix2->position.y = choix1->position.y ;
    
    choix1->surf = SDL_CreateRGBSurface(SDL_HWSURFACE, choix1->largeur, choix1->hauteur, 32, 0, 0, 0, 0);
    choix2->surf = SDL_CreateRGBSurface(SDL_HWSURFACE, choix2->largeur, choix2->hauteur, 32, 0, 0, 0, 0);
    
    SDL_FillRect( ecran, NULL,SDL_MapRGB(ecran->format,107,206,112));
    
    SDL_FillRect(choix1->surf, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_FillRect(choix2->surf, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    
    
    
   /* SDL_Surface *choix1=NULL, *choix2=NULL;
    
    bouton bout
    
    SDL_Rect position1, position2;
    
    int hauteur=300;
    int largeur=200;
    
    choix1 = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur, hauteur, 32, 0, 0, 0, 0);
    choix2 = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur, hauteur, 32, 0, 0, 0, 0);
    
    position1.x=35;
    position1.y=140;
    
    position2.x = position1.x + largeur + 30 ;
    position2.y = position1.y ;
    
    SDL_FillRect( ecran, NULL,SDL_MapRGB(ecran->format,107,206,112));
    
    SDL_FillRect(choix1, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_FillRect(choix2, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
     */
     
    SDL_BlitSurface(choix1->surf, NULL, ecran, &choix1->position);
    SDL_BlitSurface(choix2->surf, NULL, ecran, &choix2->position);
    
    SDL_Flip(ecran);
    
    wait_for_keypressed();

    SDL_FreeSurface(choix1->surf);
    SDL_FreeSurface(choix2->surf);
    
    
    free(choix1);
    free(choix2);
    
    
    
    
    
    
    
}

void fenetre_train(SDL_Surface *ecran){

    SDL_FillRect( ecran, NULL,SDL_MapRGB(ecran->format,07,06,112));
    SDL_Flip(ecran);
    
    wait_for_keypressed();
    
}


int fenetre1_2(SDL_Surface *ecran, bouton *choix1, bouton *choix2, SDL_Event event){
    
    if (event.button.y > choix1->position.y && event.button.y <= choix1->position.y+choix1->hauteur && event.button.x > choix1->position.x && event.button.x <= choix1->position.x+choix1->largeur ){
        
        fenetre_train(ecran);
        return 0;
        
        
    }
    
    else if (event.button.y > choix2->position.y && event.button.y <= choix2->position.y+choix2->hauteur && event.button.x > choix2->position.x && event.button.x <= choix2->position.x+choix2->largeur ){
        fenetre_test(ecran);
        return 0;
    }
    
    else {
    
        return 0;
    }
              
    
    
}



void wait_for_event(SDL_Surface *ecran, bouton *choix1, bouton *choix2){
    
    SDL_Event event;
    int c=1;
    
    while (c){
    
        SDL_PollEvent (&event);
        
        switch (event.type){
            
            case SDL_QUIT: 
                SDL_FreeSurface(choix1->surf);
                SDL_FreeSurface(choix2->surf);
                c=0;
                //return;
                break;
            
            case SDL_MOUSEBUTTONUP: 
                
                SDL_FreeSurface(choix1->surf); 
                SDL_FreeSurface(choix2->surf); 
                SDL_Flip(ecran);
                
                c=fenetre1_2(ecran,choix1, choix2, event);
                
                //fenetre_test(ecran);
                
               /* if (event.button.y > position1.y && event.button.y <= position1.y+HAUTEUR && event.button.x > position1.x && event.button.x <= position1.x+LARGEUR ){
                     
                    fenetre_test(ecran);
                           
                }
    
                else if (event.button.y > position1.y && event.button.y <= position1.y+HAUTEUR && event.button.x > position1.x && event.button.x <= position1.x+LARGEUR ){
                    
                    fenetre_train(ecran);
        
                 }*/
                
                //c=0;
                break;
                
                
                
                
                /* switch(fenetre){
                    case 1:
                        
                    case 2:
                        
                } */
                
            case SDL_KEYDOWN: c=0; return;
            
            default: break;
            
        
        }
        
    }
    
}

void fenetre_1(SDL_Surface *ecran){
    
    bouton *choix1=malloc(sizeof(bouton)), *choix2=malloc(sizeof(bouton));
    
    choix1->surf = NULL;
    choix2->surf = NULL;
    
    choix1 -> hauteur = 50 ;
    choix1 -> largeur = 300;
    
    choix2 -> hauteur = choix1 -> hauteur ;
    choix2 -> largeur = choix1 -> largeur;
    
    choix1->surf=SDL_CreateRGBSurface(SDL_HWSURFACE, choix1->largeur, choix1->hauteur, 32, 0, 0, 0, 0);
    choix2->surf=SDL_CreateRGBSurface(SDL_HWSURFACE, choix2->largeur, choix2->hauteur, 32, 0, 0, 0, 0);
    
    choix1->position.x=100;
    choix1->position.y=230;
    
    choix2->position.x=100;
    choix2->position.y=300;
    
    SDL_FillRect(choix1->surf, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
     SDL_FillRect(choix2->surf, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
     
     
     SDL_BlitSurface(choix1->surf, NULL, ecran, &choix1->position);
     SDL_BlitSurface(choix2->surf, NULL, ecran, &choix2->position);
    
    
    
    /*int hauteur=50;
    int largeur=300;
    
    choix1 = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur, hauteur, 32, 0, 0, 0, 0);
    choix2 = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur, hauteur, 32, 0, 0, 0, 0);
    
    position1.x=100;
    position1.y=230;
    
    position2.x=100;
    position2.y=300;
    
     SDL_FillRect(choix1, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
     SDL_FillRect(choix2, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
     
     
     SDL_BlitSurface(choix1, NULL, ecran, &position1);
     SDL_BlitSurface(choix2, NULL, ecran, &position2);*/
    
    SDL_Flip(ecran);
    
    //wait_for_keypressed();
    
    wait_for_event(ecran,choix1,choix2);
    
    
    
    wait_for_keypressed();
    
    /*SDL_FillRect( ecran, NULL,SDL_MapRGB(ecran->format,17,206,112));
    SDL_FreeSurface(choix1->surf);
    SDL_FreeSurface(choix2->surf);*/
    
    SDL_Flip(ecran);
    
    wait_for_keypressed(); 
    
    free(choix1);
    free(choix2);
    
}



