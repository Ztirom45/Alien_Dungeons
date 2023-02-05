#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "config.h"
#include "rooms.h"
#include "enemy.h"
#include "hitbox.h"

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
	SDL_Surface* Alien_Surface	= IMG_Load("images/Alien.png");
	SDL_Texture* Alien_Texture	= SDL_CreateTextureFromSurface(rend,Alien_Surface);
	
	
	SDL_Surface* surface4 	= IMG_Load("images/tile1.png");
	SDL_Surface* surface5 	= IMG_Load("images/tile2.png");
	SDL_Surface* surface6 	= IMG_Load("images/chest.png");
		

	SDL_Texture* bgtile1	= SDL_CreateTextureFromSurface(rend, surface4);
	SDL_Texture* bgtile2	= SDL_CreateTextureFromSurface(rend, surface5);
	SDL_Texture* bgtile_chest	= SDL_CreateTextureFromSurface(rend, surface6);
	SDL_Texture* tile_array[tile_count] = {bgtile1,bgtile2,bgtile_chest};
	
	SDL_FreeSurface(surface4);
	SDL_FreeSurface(surface5);
	SDL_FreeSurface(surface6);
	

	//pos
	SDL_Rect pos;
	pos.w = Alien_W*ScaleFactor;
	pos.h = Alien_H*ScaleFactor;
	pos.x = (1024 - pos.w) / 2;
	pos.y = (1024 - pos.h) / 2;
	int speed = 5;
	
	//texture array select rect
	SDL_Rect Alien_Pos;
	Alien_Pos.x = 0;
	Alien_Pos.y = 0;
	Alien_Pos.w = Alien_W;//Alien_Texture_Pos.w/IMG_MAP_W;
	Alien_Pos.h = Alien_H;//Alien_Texture_Pos.w/IMG_MAP_H;

	int frame_counter = 0;//count frames for walk animation callculation
	
	bool loop = true;
	entity Enimy1;
	
	Enimy1.speed = 5;
	Entity_LoadImage(&Enimy1,"images/Alien.png",rend);
	Enimy1.rect.x = 16;
	Enimy1.rect.y = 16;
	
	while (loop) {
		SDL_Event event;
		
		///game update
		//printf("%d %d %d %d : %d %d %d %d  \n",Enimy1.rect.x,Enimy1.rect.y,Enimy1.rect.w,Enimy1.rect.h,		pos.x,pos.y,pos.w,pos.h);
		printf("%d\n",TOUCH_RECT(79,237,40,56, 817,209,40,56));
			if(TOUCH_RECT(Enimy1.rect.x,Enimy1.rect.y,Enimy1.rect.x+Enimy1.rect.w,Enimy1.rect.y+Enimy1.rect.h,
						pos.x,pos.y,pos.w+pos.x,pos.h+pos.y)){
				loop = false;
			}
		///entity update
		Entity_Update(&Enimy1,pos);
		
		///MOVE&&player update
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
		if (keys[KEY_W]&&
			room_array[map[ry][rx]].data[(pos.y-speed)/Tile_H][pos.x/Tile_W]==0&&
			room_array[map[ry][rx]].data[(pos.y-speed)/Tile_H][(pos.x+pos.w)/Tile_W]==0){
				pos.y-=speed;
				
				Alien_Pos.y = Alien_H*3;

		}
		if (keys[KEY_S]&&((
			room_array[map[ry][rx]].data[(pos.y+pos.h+speed)/Tile_H][pos.x/Tile_W]			==0&&
			room_array[map[ry][rx]].data[(pos.y+pos.h+speed)/Tile_H][(pos.x+pos.w)/Tile_W]	==0)
			||(float)(pos.y+pos.h+speed)/Tile_H>15.5)){
				pos.y+=speed;
				Alien_Pos.y = 0;
		}
		
		if (keys[KEY_D]&&((
			room_array[map[ry][rx]].data[(pos.y)		/Tile_H][(pos.x+pos.w+speed)/Tile_W]==0&&
			room_array[map[ry][rx]].data[(pos.y+pos.h)	/Tile_H][(pos.x+pos.w+speed)/Tile_W]==0)
			||((float)(pos.x+pos.w+speed)/Tile_W)>16.0)){
				pos.x+=speed;
				Alien_Pos.y = Alien_H*2;

		}
		if (keys[KEY_A]&&
			room_array[map[ry][rx]].data[(pos.y)/Tile_H]		[(pos.x-speed)/Tile_W]==0&&
			room_array[map[ry][rx]].data[(pos.y+pos.h)/Tile_H]	[(pos.x-speed)/Tile_W]==0){
				pos.x-=speed;
				Alien_Pos.y = Alien_H;
		}
		if(keys[KEY_W]||keys[KEY_A]||keys[KEY_S]||keys[KEY_D]){
			frame_counter++;
		}
		
		//window border
		if (pos.x > win_w){
			pos.x = 1-pos.w;
			rx+=1;
		}
		if (pos.x < 1-pos.w){
			pos.x = win_w-1;
			rx-=1;
		}
		if (pos.y > win_h){
			pos.y = 1-pos.w;
			ry+=1;
		}
		if (pos.y < 1-pos.w){
			pos.y = win_h-1;
			ry-=1;
		}
		
		//walkanimation
		
		if(frame_counter>ANIMATION_DELAY_FRAMES){
			Alien_Pos.x = Frame_Array[Frame_Now];
			if(++Frame_Now>ANIMATION_FRAMES-1){
				Frame_Now = 0;
			}
			frame_counter = 0;
		}
		
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
		
		SDL_RenderCopy(rend,Alien_Texture,&Alien_Pos, &pos);

		//DRAW ENIMES
		Entity_Draw(&Enimy1,rend);
		
		// for multiple rendering
		SDL_RenderPresent(rend);

		// calculates to 60 fps
		SDL_Delay(1000 / 60);
	}

	//posroy
	SDL_DestroyTexture(Alien_Texture);
	SDL_DestroyTexture(bgtile1);
	SDL_DestroyTexture(bgtile2);
	SDL_DestroyTexture(bgtile_chest);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	 
	// close SDL
	SDL_Quit();

	return 0;
}
