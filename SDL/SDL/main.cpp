#include <iostream>
using namespace std;
#include <stdlib.h>

#include "SDL.h"

#pragma comment( lib, "SDL2.lib" )
#pragma comment( lib, "SDL2main.lib" )

int main(int argc, char* argv[])
{
	Uint32 rmask, gmask, bmask, amask;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer);
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_Event event;
	SDL_Surface* bitmap = SDL_LoadBMP("spaceship.bmp");
	SDL_Rect r;
	r.x = 270;
	r.y = 190;
	r.w = 100;
	r.h = 100;
		bool running = true;
		while (running)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
						running = false;
				}	
				
				if (event.key.keysym.sym == SDLK_RIGHT && r.x < 540)
				{
					r.x += 5;
				}
				if (event.key.keysym.sym == SDLK_LEFT && r.x > 0)
				{
					r.x -= 5;
				}
				if (event.key.keysym.sym == SDLK_UP && r.y > 0)
				{
					r.y -= 5;
				}
				if (event.key.keysym.sym == SDLK_DOWN && r.y < 380)
				{
					r.y += 5;
				}

			}
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

			//SDL_RenderClear(renderer);

			//SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			SDL_BlitSurface (bitmap, NULL, surface, &r);

			//SDL_RenderFillRect(renderer, &r);
			//SDL_RenderPresent(renderer);
			SDL_UpdateWindowSurface(window);
		}

	SDL_FreeSurface(bitmap);
	SDL_Quit();
	return(0);
}