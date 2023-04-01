//room system liberry
#include "room_data.hpp"


class room{
	public:
		int number = 0;//room number
		std::string image;
		SDL_Rect rect_dsp;
		SDL_Rect rect_img;
		
		
		void update_texture(std::string new_image){
			if(image != new_image){
				image = new_image;
				SDL_QueryTexture(textures[image], NULL, NULL, &rect_img.w, &rect_img.h);
				rect_dsp.w = rect_img.w*Scale;
				rect_dsp.h = rect_img.h*Scale;
				
				rect_img.x = 0;
				rect_img.y = 0;
				rect_dsp.x = 0;
				rect_dsp.y = 0;
			}
		};
		
		void init(){
			update_texture("img/tiles.png");
		};
		
		void draw(){
			SDL_Rect tile_rect_img;
			SDL_Rect tile_rect_dsp;
			tile_rect_img.x = 0;
			tile_rect_img.y = 0;
			tile_rect_img.w = TileImgSize;
			tile_rect_img.h = TileImgSize;
			tile_rect_dsp.w = TileImgSize*Scale;
			tile_rect_dsp.h = TileImgSize*Scale;
			
			for(int y=0;y<Room_H;y++){
				for(int x=0;x<Room_W;x++){
					tile_rect_img.x = RoomData[number][x][y]*TileImgSize;
					tile_rect_dsp.x = x*TileImgSize*Scale;
					tile_rect_dsp.y = y*TileImgSize*Scale;
					SDL_RenderCopy(rend,textures[image],&tile_rect_img, &tile_rect_dsp);
				}
			}
		};
};

static room my_room;
