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


SDL_Surface *afficher_txt (SDL_Surface *surface, char *txt ,int x, int y, TTF_Font *police, SDL_Color couleur, SDL_Surface *ecran);


void erased(SDL_Surface *img);

void wait_for_event(SDL_Surface *ecran,bouton *choix1, bouton *choix2, int level);
SDL_Surface *wait_for_draw ( SDL_Surface *draw, SDL_Surface *ecran, SDL_Rect position);
int wait_for_txt( SDL_Surface *ecran, SDL_Surface *barre, char *txt);
void wait_for_train(SDL_Surface *ecran,bouton *choix1);

void fenetre_1(SDL_Surface *ecran);
void fenetre_test(SDL_Surface *ecran);
void fenetre_train(SDL_Surface *ecran);
void fenetre_draw(SDL_Surface *ecran);
void fenetre_img(SDL_Surface *ecran);

int fenetre1_2(SDL_Surface *ecran, bouton *choix1, bouton *choix2, SDL_Event event);
int fenetre2_3(SDL_Surface *ecran, bouton *choix1, bouton *choix2, SDL_Event event);


#endif
