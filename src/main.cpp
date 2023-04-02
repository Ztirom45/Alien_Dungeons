//TODO: player.hpp: player::walk
//SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

//c++ libs
#include <string>
#include <map>
#include <dirent.h>
#include <iostream>
#include <vector>

//mocros
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_SPACE 32

//static vars
static bool loop = true;//mainloop
static SDL_Renderer* rend;
static bool keys[256];//sizeof Uint8 cant't use non letter keys

//own libs
#include "config.hpp"
#include "cvec.hpp"
#include "images.hpp"
#include "rooms.hpp"
#include "player.hpp"



void init(){
	//init
	SDL_Init(SDL_INIT_EVERYTHING);
	//create window
	SDL_Window* win = SDL_CreateWindow("Alien Dungeons - rewritten in c++",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIN_W,WIN_H, 0);
	//create renderer
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;
	rend = SDL_CreateRenderer(win,-1,render_flags);
	
	load_images();
}

void events(){
		//events
		SDL_Event event;
		const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_QUIT:
				loop = false;
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym<256){keys[event.key.keysym.sym] = true;}
				break;
			case SDL_KEYUP:
				if(event.key.keysym.sym<256){keys[event.key.keysym.sym] = false;}
				break;
			default:
				break;
			}
		}
}

int main(){
	//init
	init();
	
	//player settings 
	my_player.init("img/Alien.png");
	
	//rooms settings
	my_map.init();
	
	//gameloop
	while(loop){
		//update
		events();
		my_player.update();
		
		//draw
		SDL_RenderClear(rend);
		
		my_map.draw();
		my_player.draw();
		
		SDL_RenderPresent(rend);
		SDL_Delay(1000/60);//60 fps
	}
	//destory memory stuff
	distroy_images();
	SDL_Quit();
}
