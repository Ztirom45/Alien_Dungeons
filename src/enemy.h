#include "config.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#define PI 3.14159265358979323846
//entity type
typedef struct __entity{
	SDL_Rect rect;//rect pos
	SDL_Rect img_rect;//rect image map
	Uint8 speed;
	SDL_Texture* Texture;
}entity;

//entity functions
void Entity_LoadImage(entity *entity_ptr,char* path ,SDL_Renderer* rend){
	SDL_Surface* Surface	= IMG_Load(path);
	entity_ptr->Texture		= SDL_CreateTextureFromSurface(rend,Surface);
	SDL_QueryTexture(entity_ptr->Texture, NULL, NULL, &entity_ptr->img_rect.w, &entity_ptr->img_rect.h);
	
	entity_ptr->img_rect.x = 0;
	entity_ptr->img_rect.y= 0;
	entity_ptr->img_rect.w /= IMG_MAP_W;
	entity_ptr->img_rect.h /= IMG_MAP_H; 
	
	entity_ptr->rect.w = entity_ptr->img_rect.w *ScaleFactor;
	entity_ptr->rect.h = entity_ptr->img_rect.h *ScaleFactor;

	
}


void Entity_Update(entity *entity_ptr,SDL_Rect player_rect){
	//calculte x and y distance to player
	int player_x = (player_rect.x+(player_rect.w/2))-
					(entity_ptr->rect.x+(entity_ptr->rect.w/2));
	int player_y = player_rect.y+(player_rect.h/2)-
					(entity_ptr->rect.y+(entity_ptr->rect.h/2));
	
	int angle = atan2f(player_y, player_x)/PI*180;
	if(angle>=-125&&angle<=-45){//up
		entity_ptr->img_rect.y = 14*3;
		entity_ptr->rect.y-=entity_ptr->speed;
	}else 
	
	if(angle>=125||angle<=-125){//left
		entity_ptr->img_rect.y = 14;
		entity_ptr->rect.x-=entity_ptr->speed;
	}else 
	
	if(angle<=125&&angle>=45){//down
		entity_ptr->img_rect.y = 0;
		entity_ptr->rect.y+=entity_ptr->speed;
	}else//right
	
	{
		entity_ptr->img_rect.y = 14*2;
		entity_ptr->rect.x+=entity_ptr->speed;
	}
}

void Entity_Draw(entity *entity_ptr,SDL_Renderer *rend){
	SDL_RenderCopy(rend,
	entity_ptr->Texture,
	&entity_ptr->img_rect,
	&entity_ptr->rect);
}

