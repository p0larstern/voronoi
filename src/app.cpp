#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<stdio.h>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Renderer* rendr = NULL;

bool init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("%s\n", SDL_GetError());
        return false;
    }
    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        printf("Warning: linear texture filtering not enabled!");

    window = SDL_CreateWindow("Voronoi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        printf("%s\n", SDL_GetError());
        return false;
    }

    rendr = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(rendr == NULL)
    {
        printf("%s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(rendr, 0xFF, 0xFF, 0xFF, 0xFF);

    return true;
}

// No media loaded currently
bool loadMedia() {return true;}

void close()
{
    SDL_DestroyRenderer(rendr);
    rendr = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{

    if(!init()) printf("initialization failed!\n");
    else
    {
        if(!loadMedia()) printf("media load failed!\n");
        else
        {
            bool quit = false;
            SDL_Event evt;

            while(!quit)
            {
                while (SDL_PollEvent(&evt) != 0)
                {
                    if(evt.type == SDL_QUIT) quit=true;
                }
                SDL_SetRenderDrawColor(rendr, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(rendr);

                SDL_SetRenderDrawColor(rendr, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderDrawLine(rendr, 145.325, 153, -1497.45, -2955.64);
                SDL_RenderDrawLine(rendr, 145.325, 153, 185.478, 228.981);
                SDL_RenderDrawLine(rendr, 142.835, 299, 185.478, 228.981);
                SDL_RenderDrawLine(rendr, 142.835, 299, -1878.78, 3618.43);
                SDL_RenderDrawLine(rendr, 185.478, 228.981, 1139.97, 163.605);
                
                SDL_RenderPresent(rendr);
            }
        }
        
    }
    close();
    return 0;
}