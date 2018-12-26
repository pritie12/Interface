
# include <stdio.h>
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_ttf.h>
# include "mysdl.h"





struct bouton
{
    SDL_Surface *surf;
     int hauteur;
    int largeur;
    SDL_Rect position;
    
};
typedef struct bouton bouton;

void fenetre_1(SDL_Surface *ecran);
void wait_for_event(SDL_Surface *ecran, bouton *choix1, bouton *choix2, int level);


SDL_Surface *afficher_txt (SDL_Surface *surface, char *txt ,int x, int y, TTF_Font *police, SDL_Color couleur, SDL_Surface *ecran){
    
    SDL_Rect position;
    position.x=x;
    position.y=y;
    
    
    
    surface = TTF_RenderText_Blended(police, txt, couleur);

    SDL_BlitSurface(surface,NULL,ecran, &position);
    
    return surface;
}


void fenetre_test(SDL_Surface *ecran){
    
    SDL_WM_SetCaption("Reconnaissance de nombres - Test-",NULL);
    
//               ---initialisation des structure---
    
    struct bouton *choix1=malloc(sizeof(bouton)) , *choix2=malloc(sizeof(bouton));
    
    choix1->surf=NULL;
    choix2->surf=NULL;
    
    choix1->hauteur=250;
    choix2->hauteur=choix1->hauteur;
    
    choix1->largeur=200;
    choix2->largeur= choix1->largeur;
    
    choix1->position.x=35;
    choix1->position.y=150;
    
    choix2->position.x = choix1->position.x + choix1->largeur + 30 ;
    choix2->position.y = choix1->position.y ;
    
    choix1->surf = SDL_CreateRGBSurface(SDL_HWSURFACE, choix1->largeur, choix1->hauteur, 32, 0, 0, 0, 0);
    choix2->surf = SDL_CreateRGBSurface(SDL_HWSURFACE, choix2->largeur, choix2->hauteur, 32, 0, 0, 0, 0);
    
    SDL_FillRect( ecran, NULL,SDL_MapRGB(ecran->format,0,0,0));
    
    SDL_FillRect(choix1->surf, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_FillRect(choix2->surf, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    
    TTF_Font *police_T1=NULL, *police_T2;
    police_T1 = TTF_OpenFont("angelina.TTF", 60);
    police_T2 = TTF_OpenFont("angelina.TTF", 20);
    SDL_Surface *titre=NULL, *draw=NULL, *Retour=NULL;
    SDL_Color color_blanc= {225,225,225,0};
    SDL_Color color_noire = {0,0,0,0};
    
    
    
    
        
    
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
    afficher_txt(titre,"Test",200,50,police_T1, color_blanc,ecran);
    afficher_txt(draw, "A partir d'une Image", 35,170, police_T2, color_noire,ecran);
    afficher_txt(Retour, "Retour", 5, 480, police_T2, color_blanc,ecran);
    
    
    
    SDL_Flip(ecran);
    
    //wait_for_keypressed();

    //SDL_FreeSurface(choix1->surf);
    //SDL_FreeSurface(choix2->surf);
    SDL_FreeSurface(titre);
    SDL_FreeSurface(Retour);
    SDL_FreeSurface(draw);
    TTF_CloseFont(police_T2);
    TTF_CloseFont(police_T1);
    
    
    
    
    
    
    wait_for_event( ecran, choix1,choix2,2);
    wait_for_keypressed();
    
   /* free(choix1);
    free(choix2);*/
    

}



void fenetre_draw(SDL_Surface *ecran){
    
    SDL_WM_SetCaption("Reconnaissance de nombres- Draw",NULL);
    
   /* TTF_Font *police_T1=NULL, *police_T2;
    police_T1 = TTF_OpenFont("angelina.TTF", 60);
    police_T2 = TTF_OpenFont("angelina.TTF", 20);
    SDL_Surface *titre=NULL, *idk=NULL, *Retour=NULL;
    SDL_Color color_blanc= {225,225,225,0};
    SDL_Color color_noire = {0,0,0,0};*/
    

    SDL_FillRect( ecran, NULL,SDL_MapRGB(ecran->format,0,0,0));
   /* afficher_txt(titre,"draw",180,50,police_T1, color_blanc,ecran);
    afficher_txt(idk, "A partir d'une Image", 35,170, police_T2, color_noire,ecran);
    afficher_txt(Retour, "Retour", 5, 480, police_T2, color_blanc,ecran);*/
    
    
    
    SDL_Flip(ecran);
    
  /*  SDL_FreeSurface(titre);
    SDL_FreeSurface(Retour);
    SDL_FreeSurface(idk);
    TTF_CloseFont(police_T2);
    TTF_CloseFont(police_T1);*/
    
    wait_for_keypressed();
    
}




void fenetre_img(SDL_Surface *ecran){
    
    SDL_WM_SetCaption("Reconnaissance de nombres - Test- IMG",NULL);

    /*TTF_Font *police_T1=NULL, *police_T2;
    police_T1 = TTF_OpenFont("angelina.TTF", 60);
    police_T2 = TTF_OpenFont("angelina.TTF", 20);
    SDL_Surface *titre=NULL, *idk=NULL, *Retour=NULL;
    SDL_Color color_blanc= {225,225,225,0};
    SDL_Color color_noire = {0,0,0,0};*/
    

    SDL_FillRect( ecran, NULL,SDL_MapRGB(ecran->format,0,0,0));
   /* afficher_txt(titre,"Image",180,50,police_T1, color_blanc,ecran);
    afficher_txt(idk, "A partir d'une Image", 35,170, police_T2, color_noire,ecran);
    afficher_txt(Retour, "Retour", 5, 480, police_T2, color_blanc,ecran);*/
    
    
    
    SDL_Flip(ecran);
    
  /*  SDL_FreeSurface(titre);
    SDL_FreeSurface(Retour);
    SDL_FreeSurface(idk);
    TTF_CloseFont(police_T2);
    TTF_CloseFont(police_T1);*/
    
    wait_for_keypressed();
    
}


void fenetre_train(SDL_Surface *ecran){
    
    SDL_WM_SetCaption("Reconnaissance de nombres - Trainning",NULL);
    
    TTF_Font *police_T1=NULL, *police_T2;
    police_T1 = TTF_OpenFont("angelina.TTF", 60);
    police_T2 = TTF_OpenFont("angelina.TTF", 20);
    SDL_Surface *titre=NULL, *idk=NULL, *Retour=NULL;
    SDL_Color color_blanc= {225,225,225,0};
    SDL_Color color_noire = {0,0,0,0};
    

    SDL_FillRect( ecran, NULL,SDL_MapRGB(ecran->format,0,0,0));
    afficher_txt(titre,"Trainning",180,50,police_T1, color_blanc,ecran);
    afficher_txt(idk, "A partir d'une Image", 35,170, police_T2, color_noire,ecran);
    afficher_txt(Retour, "Retour", 5, 480, police_T2, color_blanc,ecran);
    
    
    
    SDL_Flip(ecran);
    
    SDL_FreeSurface(titre);
    SDL_FreeSurface(Retour);
    SDL_FreeSurface(idk);
    TTF_CloseFont(police_T2);
    TTF_CloseFont(police_T1);
    
    
    wait_for_keypressed();
    
}


int fenetre1_2(SDL_Surface *ecran, bouton *choix1, bouton *choix2, SDL_Event event){
    
    if (event.button.y > choix1->position.y && event.button.y <= choix1->position.y+choix1->hauteur && event.button.x > choix1->position.x && event.button.x <= choix1->position.x+choix1->largeur ){
        
        SDL_FreeSurface(choix1->surf); 
                SDL_FreeSurface(choix2->surf); 
                SDL_Flip(ecran);
        
        fenetre_train(ecran);
        return 0;
        
        
    }
    
    else if (event.button.y > choix2->position.y && event.button.y <= choix2->position.y+choix2->hauteur && event.button.x > choix2->position.x && event.button.x <= choix2->position.x+choix2->largeur ){
        
        SDL_FreeSurface(choix1->surf); 
                SDL_FreeSurface(choix2->surf); 
                SDL_Flip(ecran);
        fenetre_test(ecran);
        return 0;
    }
    
    
    else {
    
        return 1;
    }
              
    
    
}




int fenetre2_3(SDL_Surface *ecran, bouton *choix1, bouton *choix2, SDL_Event event){
    
    if (event.button.y > choix1->position.y && event.button.y <= choix1->position.y+choix1->hauteur && event.button.x > choix1->position.x && event.button.x <= choix1->position.x+choix1->largeur ){
        
        SDL_FreeSurface(choix1->surf); 
                SDL_FreeSurface(choix2->surf); 
                SDL_Flip(ecran);
        
        fenetre_img(ecran);
        return 0;
        
        
    }
    
    else if (event.button.y > 450 && event.button.y <= 500 && event.button.x > 0 && event.button.x <= 180 ){
        
        SDL_FreeSurface(choix1->surf); 
                SDL_FreeSurface(choix2->surf); 
                SDL_Flip(ecran);
                 SDL_FillRect( ecran, NULL,SDL_MapRGB(ecran->format,0,0,0));
        fenetre_1(ecran);
        
        return 0;
        
    }
    
    else if (event.button.y > choix2->position.y && event.button.y <= choix2->position.y+choix2->hauteur && event.button.x > choix2->position.x && event.button.x <= choix2->position.x+choix2->largeur ){
        
        SDL_FreeSurface(choix1->surf); 
                SDL_FreeSurface(choix2->surf); 
                SDL_Flip(ecran);
        
        fenetre_draw(ecran);
        return 0;
    }
    
    
    else {
    
        return 1;
    }
    
}



void wait_for_event(SDL_Surface *ecran, bouton *choix1, bouton *choix2, int level){
    
    SDL_Event event;
    int c=1;
    
    while (c){
    
        SDL_PollEvent (&event);
        
        switch (event.type){
            
            case SDL_QUIT: 
                SDL_FreeSurface(choix1->surf);
                SDL_FreeSurface(choix2->surf);
                c=0;
               // TTF_Quit();
                //SDL_QUIT();
                //return;
                break;
            
            case SDL_MOUSEBUTTONUP: 
                
//                 SDL_FreeSurface(choix1->surf); 
//                 SDL_FreeSurface(choix2->surf); 
//                 SDL_Flip(ecran);
                
                switch(level){
                    case 1:
                        c=fenetre1_2(ecran,choix1, choix2, event);
                        break;
                        
                    case 2:
                         c=fenetre2_3 (ecran, choix1, choix2, event);
                         break;
                         
                    default : break;
                        
                }
                        
                
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
    
    SDL_WM_SetCaption("Reconnaissance de nombres",NULL);
    
    bouton *choix1=malloc(sizeof(bouton)), *choix2=malloc(sizeof(bouton));
    
    choix1->surf = NULL;
    choix2->surf = NULL;
    
    choix1 -> hauteur = 50 ;
    choix1 -> largeur = 300;
    
    choix2 -> hauteur = choix1 -> hauteur ;
    choix2 -> largeur = choix1 -> largeur;
    
    choix1->surf=SDL_CreateRGBSurface(SDL_HWSURFACE, choix1->largeur, choix1->hauteur, 32, 0, 0, 0, 0);
    choix2->surf=SDL_CreateRGBSurface(SDL_HWSURFACE, choix2->largeur, choix2->hauteur, 32, 1, 1, 1, 0);
    
    choix1->position.x=100;
    choix1->position.y=230;
    
    choix2->position.x=100;
    choix2->position.y=300;
    
    SDL_FillRect(choix1->surf, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); 
     SDL_FillRect(choix2->surf, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); 
     
     
     SDL_BlitSurface(choix1->surf, NULL, ecran, &choix1->position);
     SDL_BlitSurface(choix2->surf, NULL, ecran, &choix2->position);
    
     
//                 ---initialisation du texte-----    
    
    
    TTF_Font *police_T1, *police_T2 ;
    SDL_Rect position_T1, position1_T2, position2_T2;
    SDL_Surface *titre, *train_txt, *test_txt = NULL;
    
    position_T1.x=130;
    position_T1.y=100;
    
    position1_T2.x=130;
    position1_T2.y=240;
    
    position2_T2.x=140;
    position2_T2.y=310;
    
    police_T1 = TTF_OpenFont("angelina.TTF", 60);
    police_T2 = TTF_OpenFont("angelina.TTF",30);
    
    SDL_Color couleurNoire = {225, 225, 225,0}; //Blanc
    
   titre = TTF_RenderText_Blended(police_T1, "Bienvenue !", couleurNoire);
   train_txt = TTF_RenderText_Blended(police_T2, "Train the neural network", couleurNoire);
   
   test_txt = TTF_RenderText_Blended(police_T2, "Tester le programme", couleurNoire);
   
   
   
   SDL_BlitSurface(titre,NULL,ecran,&position_T1);
   SDL_BlitSurface(train_txt,NULL,ecran,&position1_T2);
   SDL_BlitSurface(test_txt,NULL,ecran,&position2_T2);
    
    
    
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
    
    wait_for_event(ecran,choix1,choix2,1);
    
    
    
   // wait_for_keypressed();
    
    /*SDL_FillRect( ecran, NULL,SDL_MapRGB(ecran->format,17,206,112));
    SDL_FreeSurface(choix1->surf);
    SDL_FreeSurface(choix2->surf);*/
    
    SDL_Flip(ecran);
    
   // wait_for_keypressed(); 
    
    SDL_FreeSurface(titre);
    SDL_FreeSurface(train_txt);
    SDL_FreeSurface(test_txt);
    TTF_CloseFont(police_T1);
    TTF_CloseFont(police_T2);
    free(choix1);
    free(choix2);
    
}






