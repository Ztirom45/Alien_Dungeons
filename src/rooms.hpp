//room system liberry
#include "room_data.hpp"

class room{
	public:
		int data;
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
		
		void init(int new_data){
			data = new_data;
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
					tile_rect_img.x = RoomData[data][x][y]*TileImgSize;
					tile_rect_dsp.x = x*TileImgSize*Scale;
					tile_rect_dsp.y = y*TileImgSize*Scale;
					SDL_RenderCopy(rend,textures[image],&tile_rect_img, &tile_rect_dsp);
				}
			}
		};
};
class map{
	public:
		int room_array_data[3][3] = {
			{0,0,0},
			{0,0,0},
			{0,0,0}
		};
		
		room room_array[3][3];
		
		vec2i pos = {1,1};
		
		void init(){
			for(int x=0;x<3;x++){
				for(int y=0;y<3;y++){
					room_array[x][y].init(room_array_data[x][y]);
				}
			}
		};
		
		void draw(){
			room_array[pos.x][pos.y].draw();
		}
};

static map my_map;
