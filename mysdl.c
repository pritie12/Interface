# include <stdio.h>
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include <math.h>

SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;
    img = IMG_Load(path);
    return img;
}

SDL_Surface* open_image(SDL_Surface *img)
{

    SDL_Surface *screen;
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE | SDL_ANYFORMAT);

    if (screen == NULL)
        errx(1, "On n'a pas pu  mettre %dx,%d mode video : %s\n", img->w, img->h, SDL_GetError());

    if(SDL_BlitSurface(img, NULL, screen, NULL))
        warnx("BlitSurface error: %s\n", SDL_GetError());

    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    return screen;
}

void wait_for_keypressed(void)
{
    SDL_Event             event;
    // Infinite loop, waiting for event
    for (;;) {
        // Take an event
        SDL_PollEvent( &event );
        // Switch on event type
        switch (event.type) {
            // Someone pressed a key -> leave the function
            case SDL_KEYDOWN: return;
            default: break;
        }
        // Loop until we got the expected event
    }
}
