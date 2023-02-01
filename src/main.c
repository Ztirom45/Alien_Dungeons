#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <math.h>

#include "config.h"
#include "rooms.h"

#define UINT32SIZE 4294967296
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100


//config

static bool keys[UINT32SIZE];
 
int main(int argc, char *argv[])
{

	//init
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* win = SDL_CreateWindow("ALIEN_DUNGEONS",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,win_w, win_h, 0);

	//screen var
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

	//load image
	SDL_Surface* surface_f	= IMG_Load("images/Alien_f.png");
	SDL_Surface* surface_h	= IMG_Load("images/Alien_b.png");
	SDL_Surface* surface_r	= IMG_Load("images/Alien_r.png");
	SDL_Surface* surface_l	= IMG_Load("images/Alien_l.png");
	SDL_Surface* surface4 	= IMG_Load("images/tile1.png");
	SDL_Surface* surface5 	= IMG_Load("images/tile2.png");
	
	SDL_Texture* Alien_f	= SDL_CreateTextureFromSurface(rend, surface_f);
	SDL_Texture* Alien_h	= SDL_CreateTextureFromSurface(rend, surface_h);
	SDL_Texture* Alien_r	= SDL_CreateTextureFromSurface(rend, surface_r);
	SDL_Texture* Alien_l	= SDL_CreateTextureFromSurface(rend, surface_l);
	SDL_Texture* Alien 		= Alien_f;
	SDL_Texture* bgtile1	= SDL_CreateTextureFromSurface(rend, surface4);
	SDL_Texture* bgtile2	= SDL_CreateTextureFromSurface(rend, surface5);
	SDL_Texture* tile_array[tile_count] = {bgtile1,bgtile2};
	
	SDL_FreeSurface(surface_f);
	SDL_FreeSurface(surface_h);
	SDL_FreeSurface(surface_r);
	SDL_FreeSurface(surface_l);
	SDL_FreeSurface(surface4);
	SDL_FreeSurface(surface5);

	//player conect pos with image
	SDL_Rect pos;
	SDL_QueryTexture(Alien_f, NULL, NULL, &pos.w, &pos.h);
	pos.w *= 4;
	pos.h *= 4;
	pos.x = (1000 - pos.w) / 2;
	pos.y = (1000 - pos.h) / 2;
	int speed = 5;
	
	
	bool loop = true;
	while (loop) {
		SDL_Event event;

		//events
		const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_QUIT:
				loop = false;
				break;
			case SDL_KEYDOWN:
				keys[event.key.keysym.sym] = true;
				break;
			case SDL_KEYUP:
				keys[event.key.keysym.sym] = false;
				break;
			default:
				break;
		}

		}
		if (keys[KEY_W]){pos.y-=speed;Alien = Alien_h;}
		if (keys[KEY_S]){pos.y+=speed;Alien = Alien_f;}
		if (keys[KEY_D]){pos.x+=speed;Alien = Alien_r;}
		if (keys[KEY_A]){pos.x-=speed;Alien = Alien_l;}
		
		//boundary
		if (pos.x + pos.w > win_w)
			pos.x = 1;
		if (pos.x < 0)
			pos.x = win_w-pos.w-1;
		if (pos.y + pos.h > win_h)
			pos.y = 1;
		if (pos.y < 0)
			pos.y = win_h-pos.h-1;

		// clears the screen
		SDL_RenderClear(rend);
		
		//draw background
		SDL_Rect bgtilepos = {0,0,64,64};
		for(bgtilepos.x = 0;bgtilepos.x<win_w;bgtilepos.x+=bgtilepos.w){
			for(bgtilepos.y = 0;bgtilepos.y<win_h;bgtilepos.y+=bgtilepos.h){
				SDL_RenderCopy(rend, tile_array[room1[bgtilepos.x/bgtilepos.w][bgtilepos.y/bgtilepos.h]], NULL, &bgtilepos);
			}
		}
		
		//draw player
		SDL_RenderCopy(rend, Alien, NULL, &pos);

		// for multiple rendering
		SDL_RenderPresent(rend);

		// calculates to 60 fps
		SDL_Delay(1000 / 60);
	}

	//posroy
	SDL_DestroyTexture(Alien_f);
	SDL_DestroyTexture(Alien_l);
	SDL_DestroyTexture(Alien_r);
	SDL_DestroyTexture(Alien_h);
	SDL_DestroyTexture(Alien);
	SDL_DestroyTexture(bgtile1);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	 
	// close SDL
	SDL_Quit();

	return 0;
}
