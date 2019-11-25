#include "voronoi.hh"
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<stdio.h>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 640;
const int POINT_SCALE = 4;

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
	cout<<"\nClosing application.";
	SDL_DestroyRenderer(rendr);
    	rendr = NULL;
    	SDL_DestroyWindow(window);
	window = NULL;

    	IMG_Quit();
    	SDL_Quit();
	cout<<"\nApp closed\n";
}

void PrepareDiagram()
{
	// Add 20% margins to the bounding box.
   double dx = (X1-X0+1)/5.0; double dy = (Y1-Y0+1)/5.0;
   X0 -= dx; X1 += dx; Y0 -= dy; Y1 += dy;

   // Process the queues; select the top element with smaller x coordinate.
   while (!points.empty())
      if (!events.empty() && events.top()->x <= points.top().x)
         process_event();
      else
         process_point();

   // After all points are processed, do the remaining circle events.
   while (!events.empty())
      process_event();

   finish_edges(); // Clean up dangling edges.
}

void DrawDiagram()
{
	vector<seg*> outLines = output;
	vector<seg*>::iterator i;
	point p0, p1;

        SDL_SetRenderDrawColor(rendr, 0xFF, 0x00, 0x00, 0xFF);		//sets drawing color to red
	for(i = outLines.begin(); i != outLines.end(); i++)
	{
		p0 = (*i)->start;
		p1 = (*i)->end;
		SDL_RenderDrawLine(rendr, p0.x, p0.y, p1.x, p1.y);
	}
        SDL_RenderPresent(rendr);
	cout<<"\ncreating diagram";
}

void EmptyPointQ()
{
	while(points.empty() != true)
		points.pop();
}

void EmptyEventQ()
{
	while(events.empty() != true)
		events.pop();
}

void clearDiagram()
{
	SDL_SetRenderDrawColor(rendr, 0xFF, 0xFF, 0xFF, 0xFF);		//sets drawing color to white
	SDL_RenderClear(rendr);
	SDL_RenderPresent(rendr);
	cout<<"\nclearing diagram";
	output.clear();
	EmptyPointQ();
	EmptyEventQ();
}

void AddPointToQ(int x, int y)
{
	point p;
	p.first = 1.0*x;
	p.second = 1.0*y;
	points.push(p);
	if (p.x < X0) X0 = p.x;
    if (p.y < Y0) Y0 = p.y;
    if (p.x > X1) X1 = p.x;
    if (p.y > Y1) Y1 = p.y;
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
            SDL_Event e;
			SDL_Rect pt;
			point p;
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
										PrepareDiagram();
                        	    		DrawDiagram();
                            			break;
                        			case SDLK_x:
                            			clearDiagram();
                            			break;
                        		}
					break;
				case SDL_MOUSEBUTTONDOWN:
					cout<<"\nmouse button clicked";
					int x, y;
					SDL_GetMouseState(&x, &y);
					pt.first=x;
					pt.second=y;
					pt.h=POINT_SCALE;
					pt.w=POINT_SCALE;
					AddPointToQ(x, y);
					SDL_SetRenderDrawColor(rendr, 0xFF, 0x00, 0x00, 0xFF); 		//sets drawing color to red
					SDL_RenderFillRect(rendr, &pt);
					SDL_RenderPresent(rendr);
                    }
                }
            }
        }
        
    }
    close();
    return 0;
}
