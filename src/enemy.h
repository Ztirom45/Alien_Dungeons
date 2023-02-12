#include "config.h"
#include "path_finder.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#define PI 3.14159265358979323846
//entity type
typedef struct __entity{
	SDL_Rect rect;//rect pos
	SDL_Rect img_rect;//rect image map
	Uint8 speed;
	Uint8 frame_now;
	SDL_Texture* Texture;
	int path_pos;//position in path array
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
	
	entity_ptr->path_pos=2;
	

	
}


void Entity_Update(entity *entity_ptr,SDL_Rect player_rect){
	//calculte x and y distance to player
	bool move = false;
	int player_x = (player_rect.x+(player_rect.w/2))-
					(entity_ptr->rect.x+(entity_ptr->rect.w/2));
	int player_y = player_rect.y+(player_rect.h/2)-
					(entity_ptr->rect.y+(entity_ptr->rect.h/2));
	if(!path_finder_succes){
		int angle = atan2f(player_y, player_x)/PI*180;
		if(angle>=-125&&angle<=-45){//up
			entity_ptr->img_rect.y = 14*3;
			if(room_array[map[ry][rx]].data[(entity_ptr->rect.y-entity_ptr->speed)/Tile_H][entity_ptr->rect.x/Tile_W]==0&&
				room_array[map[ry][rx]].data[(entity_ptr->rect.y-entity_ptr->speed)/Tile_H][(entity_ptr->rect.x+entity_ptr->rect.w)/Tile_W]==0){
					entity_ptr->rect.y-=entity_ptr->speed;
					move = true;
			}
			
		}else 
		
		if(angle>=125||angle<=-125){//left
			entity_ptr->img_rect.y = 14;
			if(room_array[map[ry][rx]].data[(entity_ptr->rect.y)/Tile_H]		[(entity_ptr->rect.x-entity_ptr->speed)/Tile_W]==0&&
				room_array[map[ry][rx]].data[(entity_ptr->rect.y+entity_ptr->rect.h)/Tile_H]	[(entity_ptr->rect.x-entity_ptr->speed)/Tile_W]==0){
					entity_ptr->rect.x-=entity_ptr->speed;
					move = true;
			}
		}else 
		
		if(angle<=125&&angle>=45){//down
			entity_ptr->img_rect.y = 0;
			if((room_array[map[ry][rx]].data[(entity_ptr->rect.y+entity_ptr->rect.h+entity_ptr->speed)/Tile_H][entity_ptr->rect.x/Tile_W]==0&&
				room_array[map[ry][rx]].data[(entity_ptr->rect.y+entity_ptr->rect.h+entity_ptr->speed)/Tile_H][(entity_ptr->rect.x+entity_ptr->rect.w)/Tile_W]==0)
				||(float)(entity_ptr->rect.y+entity_ptr->img_rect.h+entity_ptr->speed)/Tile_H>15.5){
					entity_ptr->rect.y+=entity_ptr->speed;
					move = true;
			}
		}else//right
		
		
		if(angle<=45&&angle>=-45){
			entity_ptr->img_rect.y = 14*2;
			if((room_array[map[ry][rx]].data[(entity_ptr->rect.y)		/Tile_H][(entity_ptr->rect.x+entity_ptr->rect.w+entity_ptr->speed)/Tile_W]==0&&
				room_array[map[ry][rx]].data[(entity_ptr->rect.y+entity_ptr->rect.h)	/Tile_H][(entity_ptr->rect.x+entity_ptr->rect.w+entity_ptr->speed)/Tile_W]==0)
				||((float)(entity_ptr->rect.x+entity_ptr->rect.w+entity_ptr->speed)/Tile_W)>16.0){
					entity_ptr->rect.x+=entity_ptr->speed;
					move = true;
				}
		}
		
		//find path
		if(!move){
			findPath(ry,rx,(int)entity_ptr->rect.x/Tile_W,entity_ptr->rect.y/Tile_W,player_rect.x/Tile_W,player_rect.y/Tile_W);
			for(int x=0;x<room_w;x++){
				for(int y=0;y<room_h;y++){
					if (room_array[map[ry][rx]].data[x][y] == 0){
						printf(" ");
					}else{
						printf("#");
					}
					printf("%d",walked[x][y]);
					
				}
				printf("\n");
			}
			printf("A:%d %d\n",entity_ptr->rect.x/Tile_W,entity_ptr->rect.y/Tile_H);
			for(int i=0;i<path_len;i++){
				printf("%d %d\n",path[i].x,path[i].y);
			}

		}
	
	//follow path
	}else{
		bool reached_x,reached_y = false;
		//move x to path[path_pos].x
		int x_dist = path[entity_ptr->path_pos].x*64-entity_ptr->rect.x;
		int x_dirc = x_dist/abs(x_dist);
		
		printf("%d\n",x_dirc);
		
		//entity_ptr.pos.y = path[entity_ptr->path_pos].y;
		
		//move y to path[path_pos].y
		/*
		if(!(path[entity_ptr->path_pos].y==(int)(entity_ptr->rect.y)/Tile_H)){
			int y_dist = path[entity_ptr->path_pos].y*Tile_H-entity_ptr->rect.y; //distance betwen entity.rect.y and path[path_pos].y
			if(entity_ptr->speed<abs(y_dist)){
				entity_ptr->rect.y += y_dist/abs(y_dist)*entity_ptr->speed;
			}else {
				
				entity_ptr->rect.y = path[entity_ptr->path_pos].y*Tile_H;
				reached_y = true;
			}
		}
		*/
		if(reached_y){
			entity_ptr->path_pos++;
		}
	}
	//walkanimation
	if(move){
		entity_ptr->frame_now++;
		if((float)entity_ptr->frame_now/ANIMATION_DELAY_FRAMES==(float)((int)entity_ptr->frame_now/ANIMATION_DELAY_FRAMES)){
			int frame = (int)(entity_ptr->frame_now/6);
			entity_ptr->img_rect.x = Frame_Array[frame];
			if(frame>ANIMATION_FRAMES-1){
				entity_ptr->frame_now = 0;
			}
		}
	}
}

void Entity_Draw(entity *entity_ptr,SDL_Renderer *rend){
	SDL_RenderCopy(rend,
	entity_ptr->Texture,
	&entity_ptr->img_rect,
	&entity_ptr->rect);
}

