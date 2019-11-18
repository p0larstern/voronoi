#include "voronoi.hh"
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<stdio.h>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 640;

SDL_Window* window = NULL;
SDL_Renderer* rendr = NULL;

priority_queue<point,  vector<point>,  gt> points;
priority_queue<event*, vector<event*>, gt> events;

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
	cout<<"\nClosing application.";
	SDL_DestroyRenderer(rendr);
    	rendr = NULL;
    	SDL_DestroyWindow(window);
	window = NULL;

    	IMG_Quit();
    	SDL_Quit();
	cout<<"\nApp closed\n";
}

void createDiagram()
{
	vector<seg*> outLines = getOutput();
	vector<seg*>::iterator i;
	point p0, p1;

        SDL_SetRenderDrawColor(rendr, 0xFF, 0x00, 0x00, 0xFF);		//sets drawing color to red
	for(i = outLines.begin(); i != output.end(); i++)
	{
		p0 = (*i)->start;
		p1 = (*i)->end;
		SDL_RenderDrawLine(rendr, p0.x, p0.y, p1.x, p1.y);
	}
        SDL_RenderPresent(rendr);
	cout<<"\ncreating diagram";
}

void clearDiagram()
{
	SDL_SetRenderDrawColor(rendr, 0xFF, 0xFF, 0xFF, 0xFF);		//sets drawing color to white
	SDL_RenderClear(rendr);
	SDL_RenderPresent(rendr);
	cout<<"\nclearing diagram";
}

void addPoint()
{


int main(int argc, char* argv[])
{

    if(!init()) printf("initialization failed!\n");
    else
    {
        if(!loadMedia()) printf("media load failed!\n");
        else
        {
            bool quit = false;
            SDL_Event e;
	    clearDiagram();
            while(!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
			switch(e.type)
			{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:	
	                        	switch(e.key.keysym.sym)
        	                	{
						case SDLK_c:
                        	    		createDiagram();
                            			break;
                        			case SDLK_x:
                            			clearDiagram();
                            			break;
                        		}
					break;
				case SDL_MOUSEBUTTONDOWN:
					//single-click to add point
                    }
                }
            }
        }
        
    }
    close();
    return 0;
}
