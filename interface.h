# ifndef INTERFACE_H
# define INTERFACE_H


struct bouton
{
    SDL_Surface *surf;
    int hauteur;
    int largeur;
    SDL_Rect position;
};

typedef struct bouton bouton;

void wait_for_event(SDL_Surface *ecran,bouton *choix1, bouton *choix2);
void fenetre_1(SDL_Surface *ecran);
void fenetre_test(SDL_Surface *ecran);
void fenetre_train(SDL_Surface *ecran);
int fenetre1_2(SDL_Surface *ecran, bouton *choix1, bouton *choix2, SDL_Event event);


#endif
