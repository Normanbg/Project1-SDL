#include <iostream>
using namespace std;
#include <stdlib.h>

#include "SDL.h"
#define Max_Bullets 2

#pragma comment( lib, "SDL2.lib" )
#pragma comment( lib, "SDL2main.lib" )
bool running = true;
bool shoot = false;
bool mdown = false, mup = false, mright = false, mleft = false;


void movement(SDL_Rect* r)
{
	if (mup)
	{
		r->y -= 1;
	}
	else if (mdown)
	{
		r->y += 1;
	}
	else if (mright)
	{
		r->x += 1;
	}
	else if (mleft)
	{
		r->x -= 1;
	}
}

int main(int argc, char* argv[])
{
	
	SDL_Window *window;
	SDL_Renderer * renderer;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_RENDERER_PRESENTVSYNC;

	SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer);

	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_Event event;
	SDL_Surface* bitmap = SDL_LoadBMP("spaceship.bmp");
	SDL_Surface* bullet = SDL_LoadBMP("bullet.bmp");
	Uint32 white = SDL_MapRGB(surface->format, 25, 25, 255);
	SDL_Rect r;
	r.x = 270;
	r.y = 190;
	r.w = 100;
	r.h = 100;

	SDL_Rect b[Max_Bullets];
	for (int i = 0; i < Max_Bullets; ++i)
	{
		b[i].w = 50;
		b[i].h = 16;
	}

		while (running)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
						running = false;
				}	
				if (event.type == SDL_KEYDOWN)
				{
					if (event.key.repeat == 0)
					{
						if (event.key.keysym.sym == SDLK_SPACE)
						{
							//for si la bala ha estat disparada res, sino fes aixo.
							b[0].x = r.x + 50;
							b[0].y = r.y;
							shoot = true;
						}
						if (event.key.keysym.sym == SDLK_RIGHT && r.x < 590)
						{
							mright = true;
							break;
						}
						if (event.key.keysym.sym == SDLK_LEFT && r.x > 0)
						{
							mleft = true;
							break;
						}
						if (event.key.keysym.sym == SDLK_UP && r.y > 0)
						{
							mup = true;
							break;
						}
						if (event.key.keysym.sym == SDLK_DOWN && r.y < 430)
						{
							mdown = true;
							break;
						}
					}
				}
				if (event.type == SDL_KEYUP)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_UP:
						mup = false;
						break;
					case SDLK_DOWN:
						mdown = false;
						break;
					case SDLK_RIGHT:
						mright = false;
						break;
					case SDLK_LEFT:
						mleft = false;
						break;
					}
				}
			}
			movement(&r);
			if (shoot == true)
			{
				b.x += 1;
			}
			SDL_FillRect(surface, NULL, white);
			SDL_BlitSurface (bitmap, NULL, surface, &r);
			SDL_BlitSurface(bullet, NULL, surface, &b);
			SDL_UpdateWindowSurface(window);
		}

	SDL_FreeSurface(bitmap);
	SDL_Quit();
	return(0);
}
