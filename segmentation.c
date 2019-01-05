#include "segmentation.h"
extern net* a;

void horizontal(SDL_Surface *img )
{
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int cut = 1;
    int white = 1;
    int num_char=0;

    for( int j = 0; j < (img->h); j++)
    {
        for( int i = 0; i < img->w; i++)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);

            if ( !r && !b && !g)
            {
                white = 0;
                break;
            }

        }

        if( cut && !white)
        {
            pixel = SDL_MapRGB(img->format,255,0,0);
            for( int l = 0; l<(img->w) ; l++)
            {
                putpixel(img, l, j, pixel);

            }
            cut = 0;
            num_char+=1;
        }

        if( !cut && white)
        {
            pixel = SDL_MapRGB(img->format,255,0,0);
            for( int l = 0; l<(img->w) ; l++)
            {
                putpixel(img, l, j, pixel);
            }
            cut = 1;
        }
        white = 1;
    }  
    printf("%d",num_char);

}

void blacknwhite(SDL_Surface *img)
{
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    for(int i = 0; i < img->w; i++)
    {
        for(int j = 0; j < img->h; j++)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            if( r > 127 && b > 127 && g > 127)
            {
                r = 255;
                b = 255;
                g = 255;
            }
            else
            {
                r = 0;
                g = 0;
                b = 0;
            }
            pixel = SDL_MapRGB(img->format, r, g, b);
            putpixel(img, i, j, pixel);
        }
    }
}

void resize (SDL_Surface *scr ,int **src_bin, int (*dest)[28])
{
    int a, b, adlarg, adhaut;
    //adlarg=0;
    //adhaut=0;
    adlarg=28 - ((scr->w)%28);

    a= ((scr->w)+adlarg)/28 ;

    adhaut=28 - ((scr->h)%28);


    b= ((scr->h)+adhaut)/28 ;

    printf( " %d %d %d %d %d %d\n", a, adlarg , b , adhaut, scr->w , scr -> h );


    for (int i=0; i<28; i++)
    {
        //printf("aa");
        for(int j=0; j<28; j++)
        {
            /*Uint8 R, G, B;
              R=0;
              G=0;
              B=0;*/
            float  S=0;
            for (int I=0; I<a; I++)
            {
                for(int J=0; J<b; J++)
                {
                    /*Uint8 r, g, b;
                      r=0;
                      b=0;
                      g=0;*/
                    int s=0;
                    int x=(i*a)+I;
                    int y=((j*b)+J);
                    if(  (x < scr->w )&& (y < scr->h ) )
                    {

                        //Uint32 pix= getpixel(src, I+i, J+j);
                        //SDL_GetRGB(pix, src->format, &r, &g, &b);
                        s=src_bin[x][y];

                    }
                    //printf("%d ",src_bin[I+i][J+j]);
                    /*R=r+R;
                      G=g+G;
                      B=b+B;*/
                    S=S+s;
                }
                // printf("  ");
            }

            // printf(" - ");

            if ( ( S/(a*b)  ) < 0.5 )
            {
                //if ( (R/(a * b)) >127 && (B/(a * b)) > 127 && (G/(a * b)) >127){
                /*R = 255;
                  B = 255;
                  G = 255;*/
                dest[i][j]=0;
            }

            else
            {
                /*R=0;
                  G=0;
                  B=0;*/

                dest[i][j]=1;
            }
            /*Uint32 pixel = SDL_MapRGB( dest-> format, R, G, B);
              putpixel(dest, i, j, pixel);*/


            //printf("\n");

            }
        }
    }


    void binarised(SDL_Surface *img, float *tab)
    {
        blacknwhite(img);
        Uint8 r,g,b;
        Uint32 pixel;
        int **img_bin=calloc(img->w,sizeof(int * ));
        for (int i=0;i<img->w;i++)
            img_bin[i]=calloc(img->h,sizeof(int * ));

        for(int i=0; i<img->w; i++)
        {
            for (int j=0;j<img->h;j++)
            {
                pixel = getpixel(img, i, j);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);
                if( r==0 && b==0 && g ==0)
                {
                    img_bin[i][j]=1;
                }
                else
                {
                    img_bin[i][j]=0;

                }
                //printf("%d", img_bin[i][j]);

            }
            // printf("\n");
        }
        int r_img[28][28];
        //r_img = calloc(28 * sizeof(*r_img));

        for (int i=0; i<28;i++)
        {
            for (int j=0; j<28; j++)
            {
                r_img[i][j]=0;
                //printf(" %d", r_img[i][j]);

            }
        }

        resize(img,img_bin,r_img);
        int comp = 0;
        for (int j=0; j<28; j++)
        {
            for (int i=0; i<28; i++)
            {
                tab[comp] = (float) r_img[j][i];
                comp ++;
            }
        }
        free(img_bin);
        //free(r_img);
    }






    int vertical(SDL_Surface *img, int starter, int ending)
    {
        Uint32 pixel;
        Uint8 r;
        Uint8 g;
        Uint8 b;
        int cut = 1;
        int white = 1;
        int num_char=0;

        for(int i = 0; i < img->w; i++)
        {
            for(int j = 0; j < 0; j++)
            {
                pixel = getpixel(img, i, starter + j);
                putpixel(img, i, j, pixel);
            }
        }

        for( int i = 0; i < img->w; i++)
        {
            for(int j = starter; j < ending; j++)
            {
                pixel = getpixel(img, i, j);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);

                if( !r && !b && !g)
                {
                    white = 0;
                    break;
                }
            }
            if( cut && !white)
            {
                pixel = SDL_MapRGB(img->format, 255, 0, 0);
                for( int l = starter; l < ending ; l++)
                {
                    putpixel(img, i-1, l, pixel);
                }
                cut = 0;
                num_char+= 1;
            }
            if( !cut && white)
            {
                pixel = SDL_MapRGB(img->format, 255, 0, 0);
                for( int l = starter; l < ending; l++)
                {
                    putpixel(img, i, l, pixel);
                }
                cut = 1;
            }
            white = 1;
        }

        return num_char;
    }

    int separate(SDL_Surface *img )
    {
        Uint32 pixel;
        Uint8 r;
        Uint8 g;
        Uint8 b;
        int starter = 0;
        int ending = 0;
        int compt = 0;


        for ( int i = 0; i < (img->h); i++)
        {
            pixel = getpixel(img, 0, i);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);

            if( r == 255 && b==0 && g == 0)
            {

                starter = i + 1;

                for (int j = starter + 1; j < (img->h); j++)
                {
                    pixel = getpixel(img, 0, j);
                    SDL_GetRGB(pixel, img->format, &r, &g, &b);

                    if( r == 255 && b == 0 && g == 0)
                    {
                        ending = j;
                        compt += vertical(img, starter, ending);
                        break;
                    }
                }
            }
        }
        return compt;
    }
    void grayscale(SDL_Surface *img)
    { 
        Uint32 pixel;
        Uint8 r;
        Uint8 g;
        Uint8 b;
        for (int i=0; i < img->w; i++)
        {
            for(int j=0; j < img->h; j++)
            { 
                pixel = getpixel(img, i, j);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);
                Uint8 coef_r = r * 0.3;
                Uint8 coef_g = g * 0.59;
                Uint8 coef_b = b * 0.11;
                Uint8 luminance = coef_r + coef_g + coef_b;
                pixel = SDL_MapRGB(img->format, luminance, luminance, luminance);
                putpixel(img, i, j, pixel);
            }
        }
    }

    void  new_image(SDL_Surface *img, int *result)
    {
        Uint32 pix;
        Uint8 r;
        Uint8 g;
        Uint8 b;
        Uint32 rm, gm, bm, am;
        rm = 0xff000000;
        gm = 0x00ff0000;
        bm = 0x0000ff00;
        am = 0x000000ff;
        int starter = 0;
        int ending = 0;
        int start = 0;
        int end = 0;
        int ch = 0;
        int cv = 0;
        int h;
        int w;
        int c = 0;
        SDL_Surface *new;

        for (int i = 0; i < img -> h; i++)
        {
            pix = getpixel(img, 0, i);
            SDL_GetRGB(pix, img->format, &r, &g, &b);
            if ( r == 255 && b == 0 && g == 0)
            {
                starter = i + 1;
                cv ++;
                for (int j = starter + 1; j < img -> h; j++)
                {
                    pix = getpixel(img, 0, j);
                    SDL_GetRGB(pix, img->format, &r, &g, &b);
                    if (r == 255 && b == 0 && g == 0)
                    {
                        ending = j - 1;
                        for (int k = 0; k < img -> w; k++)
                        {
                            pix = getpixel(img, k, starter);
                            SDL_GetRGB(pix, img->format, &r, &g, &b);
                            if (r == 255 && g == 0 && b == 0)
                            {
                                start = k + 1;
                                ch ++;
                            }
                            for (int l = start + 1; l < img->w; l++)
                            {
                                pix = getpixel(img,l, starter);
                                SDL_GetRGB(pix, img->format, &r, &g, &b);
                                if(r == 255 && g == 0 && b == 0)
                                {
                                    end = l - 1;
                                }
                            }
                        }
                        if ( cv % 2 == 1 && ch % 2 == 1)
                        {
                            h = ending - starter;
                            w = end - start;
                            new = SDL_CreateRGBSurface(0, w, h, 32, rm, gm, bm, am);
                            for (int z = 0; z < h; z++)
                            {
                                for (int x = 0; x < w; x++)
                                {
                                    pix = getpixel(img, start + w, starter + h);
                                    putpixel(new, w, h, pix);
                                }
                            }
                            binarised(new, a -> input);
                            feedforward(a);
                            result[c] = max_array(a -> output, a -> nbr_output);
                            c++;
                        }
                        break;
                    }
                }
            }
        }
    }

