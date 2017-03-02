#include <iostream>
using namespace std;
#include <stdlib.h>

#include "SDL.h"

#pragma comment( lib, "SDL2.lib" )
#pragma comment( lib, "SDL2main.lib" )

int main(int argc, char* argv[])
{
	SDL_Surface *surface;
	Uint32 rmask, gmask, bmask, amask;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer);
	SDL_Rect r;
	r.x = 275;
	r.y = 165;
	r.w = 150;
	r.h = 150;
	SDL_Event event;
	
		bool running = true;
		while (running)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
						running = false;
				}				
			}
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

			SDL_RenderClear(renderer);

			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

			SDL_RenderFillRect(renderer, &r);
			SDL_RenderPresent(renderer);
		}

	SDL_Quit();
	return(0);
}