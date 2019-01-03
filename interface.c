
# include <stdio.h>
# include <stdlib.h>
#include <string.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_ttf.h>
# include "mysdl.h"
# include "segmentation.h"




//             ----------initialisations des struc-------------------
struct bouton
{
    SDL_Surface *surf;
     int hauteur;
    int largeur;
    SDL_Rect position;
    
};
typedef struct bouton bouton;


//             ----------initialisation des fonctions ----------------

void fenetre_1(SDL_Surface *ecran);
void wait_for_event(SDL_Surface *ecran, bouton *choix1, bouton *choix2, int level);
void fenetre_test(SDL_Surface *ecran);
int wait_for_txt(SDL_Surface *ecran, SDL_Surface *barre, char *txt);
void wait_for_train(SDL_Surface *ecran,bouton *choix1);


//              ----------------------Fonctions----------------



void erased(SDL_Surface *img){    //rend l'image toute blanche
    
    Uint32 pixel=SDL_MapRGB(img->format,255,255,255);

    for (int i = 0 ; i< img->w ; i++){
        for(int j=0;j<img->h;j++){
        putpixel(img,i,j,pixel);
            
        }
        
    }
    
}



SDL_Surface *wait_for_draw (SDL_Surface *draw, SDL_Surface *ecran, SDL_Rect position){
    SDL_Event event;
    int c=1;
    while(c==1){
        SDL_PollEvent (&event);
        
        SDL_Rect clic;
        
        switch(event.type){
            
            case SDL_MOUSEBUTTONDOWN:
                
                
                while(event.type!= SDL_MOUSEBUTTONUP){
                    
                    
                    
                
                    SDL_PollEvent (&event);
                    
                    if ( event.type==SDL_MOUSEBUTTONUP && event.button.y > 450 && event.button.y <= 500 && event.button.x > 0 && event.button.x <= 180 ){  //RETOUR
                        SDL_FillRect( ecran, NULL,SDL_MapRGB(ecran->format,0,0,0));
                        fenetre_test(ecran);
                       // break;
                        return ecran;
                        
                    }
                    
                   else if (event.button.button == SDL_BUTTON_RIGHT){
                 erased(draw);
                 SDL_BlitSurface(draw,NULL, ecran, &position);
                
                SDL_Flip(ecran);
                }
                
                
                   else if (event.type== SDL_MOUSEMOTION){
                    
                        clic.x=event.motion.x;
                        clic.y=event.motion.y;
                        
                        
                        if (clic.x >= position.x && clic.x < ((draw->w)+position.x) &&clic.y>= position.y && clic.y < (draw->h)+position.y){
                        
                            Uint32 pixel=SDL_MapRGB(draw->format,255,26,95);
                            
                            for(int i=-15; i<15;i++){
                                for (int j=-15; j<15; j++){
                                    
                                    if (clic.x+i >= position.x && clic.x+i < ((draw->w)+position.x) &&clic.y+j>= position.y && clic.y+j < (draw->h)+position.y){
                            
                            putpixel(draw,clic.x+i-position.x,clic.y+j-position.y,pixel);
                            
                                    }
                                }
                                
                                
                            }
                            
                                            
                            SDL_BlitSurface(draw,NULL, ecran, &position);
                
                            SDL_Flip(ecran);
                        
                        }
                    }
                
                }
                
                
                
                
                break;
                
                
            /*case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_RIGHT){
                 erased(draw);   
                }
                break;
            */
            
            
            case SDL_KEYDOWN:
                
                binarised(draw);
                
                
                c=0; 
                return draw;
            
            default: break;
        }
                
       // wait_for_keypressed();
        
    }
    
    
    return draw;
    
}





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
    SDL_Surface *titre=NULL, *draw_t=NULL,*img_t=NULL, *Retour=NULL, *draw=NULL, *img=NULL;
    SDL_Rect pos_img, pos_draw;
    SDL_Color color_blanc= {225,225,225,0};
    SDL_Color color_noire = {0,0,0,0};
    
    pos_draw.x=300;
    pos_draw.y=230;
    pos_img.x=70;
    pos_img.y=230;
    
    img=load_image("img.png");
    draw=load_image("draw-a-picture.png");
    
        
   
     
    SDL_BlitSurface(choix1->surf, NULL, ecran, &choix1->position);
    SDL_BlitSurface(choix2->surf, NULL, ecran, &choix2->position);
    afficher_txt(titre,"Test",200,50,police_T1, color_blanc,ecran);
    afficher_txt(draw_t, "A partir d'une Image", choix1->position.x+5,choix1->position.y+20, police_T2, color_noire,ecran);
    afficher_txt(img_t, "A partir d'un dessin numerique", choix2->position.x+5,choix2->position.y+20, police_T2, color_noire,ecran);
    afficher_txt(Retour, "Retour", 5, 480, police_T2, color_blanc,ecran);
     SDL_BlitSurface(img, NULL, ecran, &pos_img);
     SDL_BlitSurface(draw, NULL, ecran, &pos_draw);
    
    
    
    SDL_Flip(ecran);
    
    //wait_for_keypressed();

    //SDL_FreeSurface(choix1->surf);
    //SDL_FreeSurface(choix2->surf);
    SDL_FreeSurface(titre);
    SDL_FreeSurface(Retour);
    SDL_FreeSurface(draw_t);
    SDL_FreeSurface(img_t);
    SDL_FreeSurface(draw);
    SDL_FreeSurface(img);
    TTF_CloseFont(police_T2);
    TTF_CloseFont(police_T1);
    
    
    
    
    
    
    wait_for_event( ecran, choix1,choix2,2);
    wait_for_keypressed();
    
   /* free(choix1);
    free(choix2);*/
    

}



void fenetre_draw(SDL_Surface *ecran){
    
    SDL_WM_SetCaption("Reconnaissance de nombres- Draw",NULL);
    
    TTF_Font *police_T1=NULL, *police_T2;
    police_T1 = TTF_OpenFont("angelina.TTF", 72);
    police_T2 = TTF_OpenFont("angelina.TTF", 20);
    SDL_Surface *titre=NULL, *step1=NULL, *step2=NULL, *step3=NULL, *resultat_txt=NULL,* resultat =NULL,*Retour=NULL;
    SDL_Color color_blanc= {225,225,225,0};
  //  SDL_Color color_noire = {0,0,0,0};
    

    SDL_FillRect( ecran, NULL,SDL_MapRGB(ecran->format,0,0,0));
    
    SDL_Surface *draw = load_image("draw.png");
     SDL_Rect position;
     
     position.x=20;
     position.y=125;
     
    SDL_BlitSurface(draw,NULL, ecran, &position);
    
    
    
    
    afficher_txt(titre,"Draw",215,30,police_T1, color_blanc,ecran);
    afficher_txt(step1, "-Dessinez le chiffre", 345,160, police_T2, color_blanc,ecran);
    afficher_txt(step2, "- Clic droit : effacer",345,200, police_T2,color_blanc,ecran);
    afficher_txt(step3,"-Entree : lancer le programme",345,240,police_T2, color_blanc, ecran);
    afficher_txt (resultat_txt, "Resultat",345,300,police_T1, color_blanc,ecran);
    afficher_txt(resultat, "3", 355, 360,police_T1,color_blanc,ecran);
    
    afficher_txt(Retour, "Retour", 5, 480, police_T2, color_blanc,ecran);
   
    SDL_Flip(ecran);
    
   wait_for_draw(draw,ecran, position);
    
    
    
    SDL_Flip(ecran);
    
    SDL_FreeSurface(titre);
    SDL_FreeSurface(Retour);
    SDL_FreeSurface(step1);
    SDL_FreeSurface(step2);
    SDL_FreeSurface(step3);
    SDL_FreeSurface(resultat_txt);
    SDL_FreeSurface(resultat);
    TTF_CloseFont(police_T2);
    TTF_CloseFont(police_T1);
    
    wait_for_keypressed();
    
}




void fenetre_img(SDL_Surface *ecran){
    
    SDL_WM_SetCaption("Reconnaissance de nombres - Test- IMG",NULL);

    int continuer=0;
    
    TTF_Font *police_T1=NULL, *police_T2, *police_T3;
    police_T1 = TTF_OpenFont("angelina.TTF", 60);
    police_T2 = TTF_OpenFont("angelina.TTF", 30);
    police_T3 = TTF_OpenFont("angelina.TTF", 20);
    SDL_Surface *titre=NULL, *idk=NULL, *Retour=NULL, *barre=NULL, *img=NULL, *error_txt=NULL, *txt=NULL, *resultat_txt=NULL;
    SDL_Rect pos_barre,pos_img;
    
    pos_barre.x=55;
    pos_barre.y=100;
    
    pos_img.x= 20;
    pos_img.y=170;
    SDL_Color color_blanc= {225,225,225,0};
    SDL_Color color_noire = {0,0,0,0};
    
    barre = SDL_CreateRGBSurface(SDL_HWSURFACE,270, 32, 32,0 , 0,0, 0);
    SDL_FillRect( ecran, NULL,SDL_MapRGB(ecran->format,0,0,0));
    SDL_FillRect( barre, NULL,SDL_MapRGB(ecran->format,255,255,255));
    SDL_BlitSurface(barre, NULL, ecran, &pos_barre); 
    afficher_txt(titre,"Image",180,30,police_T1, color_blanc,ecran);
    afficher_txt(idk, "Entrez le nom de l'image", 60,105, police_T3, color_noire,ecran);
    afficher_txt(Retour, "Retour", 5, 480, police_T3, color_blanc, ecran) ;
    
    
    
    SDL_Flip(ecran);
    
    char img_name[100];
    continuer=wait_for_txt(ecran,barre,img_name);

    while(continuer==0){
    
    img=load_image(img_name);
    
    
     while(img==NULL && continuer==0){
         //img_name={0};
         afficher_txt(error_txt,"L'image n'a pas ete trouve veuillez reessayer",55,140,police_T3, color_blanc,ecran);
         continuer=wait_for_txt(ecran, barre,img_name);
         img=load_image(img_name);
         
    }
    
    
    SDL_BlitSurface(img,NULL, ecran, &pos_img);
    SDL_Flip(ecran);
    wait_for_keypressed();
    
    afficher_txt(txt,"Sur l'image il y a les chiffres:",75,430, police_T2, color_blanc,ecran);
    afficher_txt(resultat_txt , "126875", 75,455, police_T2, color_blanc, ecran);
    
    wait_for_keypressed();
    continuer=1;
    
    }
    wait_for_keypressed();
    
    SDL_FreeSurface(titre);
    SDL_FreeSurface(barre);
    SDL_FreeSurface(img);
    SDL_FreeSurface(Retour);
    SDL_FreeSurface(idk);
    TTF_CloseFont(police_T2);
    TTF_CloseFont(police_T1);
    
    wait_for_keypressed();
    
}


void fenetre_train(SDL_Surface *ecran){
    
    SDL_WM_SetCaption("Reconnaissance de nombres - Trainning",NULL);
    
    //int continuer=1;
    
    TTF_Font *police_T1=NULL, *police_T2, *police_T3;
    police_T1 = TTF_OpenFont("angelina.TTF", 60);
    police_T2 = TTF_OpenFont("angelina.TTF", 30);
    police_T3 = TTF_OpenFont("angelina.TTF", 20);
    SDL_Surface *titre=NULL, *idk=NULL, *Retour=NULL, *go=NULL;
    bouton *go_train=malloc(sizeof(bouton));
    
    SDL_Color color_blanc= {225,225,225,0};
    SDL_Color color_noire = {0,0,0,0};
    
    go_train->surf=NULL;
    go_train->hauteur=50;
    go_train->largeur=100;
    go_train->surf=SDL_CreateRGBSurface(SDL_HWSURFACE, go_train->largeur, go_train->hauteur, 32, 0, 0, 0, 0);
    go_train->position.x=200;
    go_train->position.y=220;
    SDL_FillRect(go_train->surf, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 

    SDL_FillRect( ecran, NULL,SDL_MapRGB(ecran->format,0,0,0));
    afficher_txt(titre,"Trainning",180,50,police_T1, color_blanc,ecran);
    afficher_txt(idk, "L'entrainement peut mettre du temps", 50,170, police_T2, color_blanc,ecran);
    
    SDL_BlitSurface(go_train->surf, NULL, ecran, &go_train->position);
    afficher_txt(go, "GO", 240,235, police_T3, color_noire,ecran);
    afficher_txt(Retour, "Retour", 5, 480, police_T3, color_blanc,ecran);
    
    
    
    SDL_Flip(ecran);
    
    wait_for_train(ecran,go_train);
    
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
    
    else if (event.button.y > 450 && event.button.y <= 500 && event.button.x > 0 && event.button.x <= 180 ){  //RETOUR
        
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




void wait_for_train(SDL_Surface *ecran, bouton *choix1){
     SDL_Event event;
    int c=1;
    
    SDL_Surface *msg=NULL;
    TTF_Font *police_T2 = TTF_OpenFont("angelina.TTF", 40);
    SDL_Color color_blanc= {225,225,225,0};
    
    while (c){
    
        SDL_PollEvent (&event);
        
        switch (event.type){
            
            
            case SDL_MOUSEBUTTONUP:
            
            
            if (event.button.y > 450 && event.button.y <= 500 && event.button.x > 0 && event.button.x <= 180 ){  //RETOUR
        
      
                 SDL_Flip(ecran);
                 SDL_FillRect( ecran, NULL,SDL_MapRGB(ecran->format,0,0,0));
                fenetre_1(ecran);
        
                c= 0;
        
            
        }
        
        else if(event.button.y > choix1->position.y && event.button.y <= choix1->position.y+choix1->hauteur && event.button.x > choix1->position.x && event.button.x <= choix1->position.x+choix1->largeur){
            afficher_txt(msg,"Le train est lance",150,300,police_T2,color_blanc
            ,ecran);
            SDL_Flip(ecran);
            
        }
        break;
        
            default : break;
        
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
    
    
    
   
    
    SDL_Flip(ecran);
    
    //wait_for_keypressed();
    
    wait_for_event(ecran,choix1,choix2,1);
    
    
    
   // wait_for_keypressed();
    
        
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




int wait_for_txt( SDL_Surface *ecran, SDL_Surface *barre , char* txt){
    SDL_Event event;
  
    txt[0]='\0';
    int c=1;
    int pos=0;
    SDL_Rect pos_b;
    TTF_Font *police_T1;
   
   SDL_Surface *titre=NULL;
   police_T1 = TTF_OpenFont("angelina.TTF", 20);
   SDL_Color couleurNoire = {255, 0, 0,0};
    pos_b.x=55;
    pos_b.y=100;
    
    while (c==1 && pos<100-1&&pos>=0){
        //SDL_PollEvent(&event);
        SDL_WaitEvent(&event);
        
        switch(event.type){
        
        case SDL_MOUSEBUTTONUP: 
            if (event.button.y > 450 && event.button.y <= 500 && event.button.x > 0 && event.button.x <= 180 ){
                fenetre_test(ecran);
                c=0;
                return 1;
                break;
                
            }
            else{break;}
        
        case SDL_KEYDOWN:
            
            switch(event.key.keysym.sym){
                case SDLK_a:txt[pos]='a'; pos++;txt[pos]='\0';break;
                case SDLK_b:txt[pos]='b'; pos++;txt[pos]='\0';break;
                case SDLK_c:txt[pos]='c'; pos++;txt[pos]='\0';break;
                case SDLK_d:txt[pos]='d'; pos++;txt[pos]='\0';break;
                case SDLK_e:txt[pos]='e'; pos++;txt[pos]='\0';break;
                case SDLK_f:txt[pos]='f'; pos++;txt[pos]='\0';break;
                case SDLK_g:txt[pos]='g'; pos++;txt[pos]='\0';break;
                case SDLK_h:txt[pos]='h'; pos++;txt[pos]='\0';break;
                case SDLK_i:txt[pos]='i'; pos++;txt[pos]='\0';break;
                case SDLK_j:txt[pos]='j'; pos++;txt[pos]='\0';break;
                case SDLK_k:txt[pos]='k'; pos++;txt[pos]='\0';break;
                case SDLK_l:txt[pos]='l'; pos++;txt[pos]='\0';break;
                case SDLK_m:txt[pos]='m'; pos++;txt[pos]='\0';break;
                case SDLK_n:txt[pos]='n'; pos++;txt[pos]='\0';break;
                case SDLK_o:txt[pos]='o'; pos++;txt[pos]='\0';break;
                case SDLK_p:txt[pos]='p'; pos++;txt[pos]='\0';break;
                case SDLK_q:txt[pos]='q'; pos++;txt[pos]='\0';break;
                case SDLK_r:txt[pos]='r'; pos++;txt[pos]='\0';break;
                case SDLK_s:txt[pos]='s'; pos++;txt[pos]='\0';break;
                case SDLK_t:txt[pos]='t'; pos++;txt[pos]='\0';break;
                case SDLK_u:txt[pos]='u'; pos++;txt[pos]='\0';break;
                case SDLK_v:txt[pos]='v'; pos++;txt[pos]='\0';break;
                case SDLK_w:txt[pos]='w'; pos++;txt[pos]='\0';break;
                case SDLK_x:txt[pos]='x'; pos++;txt[pos]='\0';break;
                case SDLK_y:txt[pos]='y'; pos++;txt[pos]='\0';break;
                case SDLK_z:txt[pos]='z'; pos++;txt[pos]='\0';break;
                case SDLK_UNDERSCORE:txt[pos]='_'; pos++;txt[pos]='\0';break;
                case SDLK_KP0:txt[pos]='0'; pos++;txt[pos]='\0';break;
                case SDLK_KP1:txt[pos]='1'; pos++;txt[pos]='\0';break;
                case SDLK_KP2:txt[pos]='2';pos++;txt[pos]='\0';break;
                case SDLK_KP3:txt[pos]='3'; pos++;txt[pos]='\0';break;
                case SDLK_KP4:txt[pos]='4'; pos++;txt[pos]='\0';break;
                case SDLK_KP5:txt[pos]='5'; pos++;txt[pos]='\0';break;
                case SDLK_KP6:txt[pos]='6'; pos++;txt[pos]='\0';break;
                case SDLK_KP7:txt[pos]='7'; pos++;txt[pos]='\0';break;
                case SDLK_KP8:txt[pos]='8'; pos++;txt[pos]='\0';break;
                case SDLK_KP9:txt[pos]='9'; txt[pos]='\0';pos++;break;
                case SDLK_KP_PERIOD:txt[pos]='.'; pos++; txt[pos]='\0';break;
                case SDLK_RETURN: txt[pos]='\0'; c=0;break;
                case SDLK_BACKSPACE:txt[pos]='\0'; pos=pos-1;break;
                default: printf("%s \n" ,txt); break;
            }
            
            SDL_BlitSurface(barre, NULL, ecran, &pos_b);
            afficher_txt(titre,txt,pos_b.x + 5, pos_b.y+5,police_T1, couleurNoire,ecran);
            SDL_Flip(ecran);
            break;
        
            default: break;
        }
       
    
        
        
        
    }
    
    printf(" %s " ,txt);

    return 0;
}



