#include <iostream>
using namespace std;
#include <stdlib.h>
#include "SDL_image.h"
#include "SDL.h"
#define Max_Bullets 2

#pragma comment( lib, "SDL2_image.lib" )
#pragma comment( lib, "SDL2main.lib" )
#pragma comment( lib, "SDL2.lib" )

bool running = true;
bool shoot[Max_Bullets];
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
	int flags = IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	
	SDL_Window *window;
	SDL_Renderer * renderer;
	
	//renderer = SDL_;SDL_RENDERER_PRESENTVSYNC;
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	

	SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer);

	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_Surface *image;
	image = IMG_Load("sprite1.png");
	SDL_Event event;
	
	SDL_Texture* background = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("background.bmp"));
	SDL_Texture* sprite = SDL_CreateTextureFromSurface(renderer,image);
	SDL_Texture* bitmap = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("spaceship.bmp"));
	SDL_Texture* bullet = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("bullet.bmp"));

	//SDL_Rect sprite;

	SDL_Rect r;
	r.x = 270;
	r.y = 190;
	r.w = 100;
	r.h = 100;

	SDL_Rect bg1;
	bg1.w = 960;
	bg1.h = 480;
	bg1.x = 0;
	bg1.y = 0;

	SDL_Rect bg2;
	bg2.w = 960;
	bg2.h = 480;
	bg2.x = 960;
	bg2.y = 0;

	for (int i = 0; i < Max_Bullets; ++i)
	{
		shoot[i] = false;
	}

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
							for (int i = 0; i < Max_Bullets; ++i)
							{
								if (shoot[i] == false)
								{
									b[i].x = r.x + 50;
									b[i].y = r.y;
									shoot[i] = true;
								}
							}
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
			for (int i = 0; i < Max_Bullets; ++i)
			{
				if (shoot[i] == true)
				{
					b[i].x += 1;
					if (b[i].x >= 640)
					{
						shoot[i] = false;
					}
				}
			}
			if (bg1.x == -1280) {
				bg1.x = 1280;
			}

			if (bg2.x == -1280) {
				bg2.x = 1280;
			}

			bg1.x -= 1;
			bg2.x -= 1;
			
			SDL_RenderCopy(renderer, background, NULL, &bg2);

			SDL_RenderCopy(renderer, background, NULL, &bg1);

			SDL_RenderCopy(renderer, bitmap, NULL, &r);

			SDL_RenderCopy(renderer, bullet, NULL, &b[0]);



			SDL_RenderPresent(renderer);

		}
	IMG_Quit();
	SDL_Quit();
	return(0);
}
