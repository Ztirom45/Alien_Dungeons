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
		
		///MOVE
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
		printf("%d %d\n",pos.x,pos.y);
		if (keys[KEY_W]&&
			room_array[map[ry][rx]].data[(pos.y-speed)/Tile_H][pos.x/Tile_W]!=1&&
			room_array[map[ry][rx]].data[(pos.y-speed)/Tile_H][(pos.x+pos.w)/Tile_W]!=1){
				pos.y-=speed;Alien = Alien_h;
		}
		if (keys[KEY_S]&&((
			room_array[map[ry][rx]].data[(pos.y+pos.h+speed)/Tile_H][pos.x/Tile_W]			!=1&&
			room_array[map[ry][rx]].data[(pos.y+pos.h+speed)/Tile_H][(pos.x+pos.w)/Tile_W]	!=1)||rx>room_h-2)){
				pos.y+=speed;Alien = Alien_f;
		}
		
		if (keys[KEY_D]&&((
			room_array[map[ry][rx]].data[(pos.y)/Tile_H]		[(pos.x+pos.w+speed)/Tile_W]!=1&&
			room_array[map[ry][rx]].data[(pos.y+pos.h)/Tile_H]	[(pos.x+pos.w+speed)/Tile_W]!=1)||rx>room_w-2)){
				pos.x+=speed;Alien = Alien_r;
		}
		if (keys[KEY_A]&&
			room_array[map[ry][rx]].data[(pos.y)/Tile_H]		[(pos.x-speed)/Tile_W]!=1&&
			room_array[map[ry][rx]].data[(pos.y+pos.h)/Tile_H]	[(pos.x-speed)/Tile_W]!=1){
				pos.x-=speed;Alien = Alien_l;
		}
		
		//window border
		if (pos.x-speed > win_w){
			pos.x = 1;
			rx+=1;
		}
		if (pos.x+speed < -pos.w-1){
			pos.x = win_w-pos.w-1;
			rx-=1;
		}
		if (pos.y-speed > win_h){
			pos.y = 1;
			ry+=1;
		}
		if (pos.y+speed < -pos.h-1){
			pos.y = win_h-pos.h-1;
			ry-=1;
		}
		
		
		//touch
		
		
		///DRAW
		// clears the screen
		SDL_RenderClear(rend);
		
		//draw background
		
		SDL_Rect bgtilepos = {0,0,Tile_W,Tile_H};
		for(bgtilepos.x = 0;bgtilepos.x<win_w;bgtilepos.x+=bgtilepos.w){
			for(bgtilepos.y = 0;bgtilepos.y<win_h;bgtilepos.y+=bgtilepos.h){
				SDL_RenderCopy(rend, tile_array[room_array[map[ry][rx]].data[(int)(bgtilepos.y/bgtilepos.h)][(int)(bgtilepos.x/bgtilepos.w)]], NULL, &bgtilepos);
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
