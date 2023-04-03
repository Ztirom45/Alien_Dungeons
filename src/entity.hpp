class entity{
	public:
		SDL_Rect rect_dsp;	//size and pos on display
		SDL_Rect rect_img;	//pixel positions in images
		std::string costume;//texture array
		int lives = 10;
		int speed = 2;
		int AnimationFrame = 0;//tick Counter
		bool walked = false;//true if the player walked
		
		
	void update_texture(std::string new_costume,vec2i pos){
		costume = new_costume;
		SDL_QueryTexture(textures[costume], NULL, NULL, &rect_img.w, &rect_img.h);
		rect_img.w = rect_img.w/Map_W;
		rect_img.h = rect_img.h/Map_H;
		rect_img.x = pos.x*rect_img.w;
		rect_img.y = pos.y*rect_img.h;
		
		rect_dsp.w = rect_img.w*Scale;
		rect_dsp.h = rect_img.h*Scale;
		
	}
	
	void init(std::string new_costume){
		rect_dsp.x = 256;
		rect_dsp.y = 256;
		rect_img.x = 0;
		rect_img.y = 0;
		update_texture(new_costume,{0,0});
	};
	
	void draw(){
		SDL_RenderCopy(rend,textures[costume],&rect_img, &rect_dsp);
	};
	
	void walk(bool var){
		if(var){
			if(++AnimationFrame>AnimationFPS*AnimationFrameCount){
				AnimationFrame = 0;
			}else{
				if((float)((int)(AnimationFrame/AnimationFPS))==(float)AnimationFrame/AnimationFPS){
					rect_img.x=(AnimationFrame-AnimationFPS)/AnimationFPS*rect_img.w;
				}
			}
		}
	}
	void update(){
		//control
		walked = false;
		int RoomNow	= my_map.room_array[my_map.pos.x][my_map.pos.y].data;
		
		//Up
		if(rect_dsp.y>my_player.rect_dsp.y){
			if(
			RoomData[RoomNow][(rect_dsp.x)/TileImgSize/Scale][(rect_dsp.y-speed)/TileImgSize/Scale]!=2&&
			RoomData[RoomNow][(rect_dsp.x+rect_dsp.w)/TileImgSize/Scale][(rect_dsp.y-speed)/TileImgSize/Scale]!=2
			){//block colision
					rect_dsp.y -=speed;
					rect_img.y = 3*rect_img.h;//row 3
					walked = true;
			}
		}
		
		//Down
		if(rect_dsp.y<my_player.rect_dsp.y){
			if(
			(RoomData[RoomNow][(rect_dsp.x)/TileImgSize/Scale][(rect_dsp.y+rect_dsp.h+speed)/TileImgSize/Scale]!=2&&
			 RoomData[RoomNow][(rect_dsp.x+rect_dsp.w)/TileImgSize/Scale][(rect_dsp.y+rect_dsp.h+speed)/TileImgSize/Scale]!=2)
			||(float)(rect_dsp.y+rect_dsp.h+speed)/TileImgSize/Scale>15.5
			){//block colision
				rect_dsp.y +=speed;
				rect_img.y = 0;//row 0
				walked = true;
			}
		}
		
		//left
		if(rect_dsp.x>my_player.rect_dsp.x){
				if(
					RoomData[RoomNow][(rect_dsp.x-speed)/TileImgSize/Scale][(rect_dsp.y)/TileImgSize/Scale]!=2&&
					RoomData[RoomNow][(rect_dsp.x-speed)/TileImgSize/Scale][(rect_dsp.y+rect_dsp.h)/TileImgSize/Scale]!=2
					){//block colision
					rect_dsp.x -= speed;
					rect_img.y = rect_img.h;//row 1
					walked = true;
				}
		}
		//Right
		if(rect_dsp.x<my_player.rect_dsp.x){
			if(
			(RoomData[RoomNow][(rect_dsp.x+rect_dsp.w+speed)/TileImgSize/Scale][(rect_dsp.y)/TileImgSize/Scale]!=2&&
			 RoomData[RoomNow][(rect_dsp.x+rect_dsp.w+speed)/TileImgSize/Scale][(rect_dsp.y+rect_dsp.h)/TileImgSize/Scale]!=2)
			||((float)(rect_dsp.x+rect_dsp.w+speed)/TileImgSize/Scale)>16.0){
				rect_dsp.x +=speed;
				rect_img.y = 2*rect_img.h;//row 2
				walked = true;
			}
		}
		
		
		//lives
		if(lives<=0){
			loop = false;
		}
		//animation
		walk(walked);
	}
};

static entity my_enemy;
