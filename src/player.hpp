class player{
	public:
		SDL_Rect rect_dsp;	//size and pos on display
		SDL_Rect rect_img;	//pixel positions in images
		std::string costume;//texture array
		int lives = 10;
		int speed = 5;
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
		
		if(keys[KEY_W]){
			if(rect_dsp.y-speed<=0){//border
				rect_dsp.y=WIN_H-1;
				my_map.pos.y-=1;
				//my_map.pos.y
			}else{
				if(
				RoomData[RoomNow][(rect_dsp.x)/TileImgSize/Scale][(rect_dsp.y-speed)/TileImgSize/Scale]!=2&&
				RoomData[RoomNow][(rect_dsp.x+rect_dsp.w)/TileImgSize/Scale][(rect_dsp.y-speed)/TileImgSize/Scale]!=2
				){//block colision
						rect_dsp.y -=speed;
						rect_img.y = 3*rect_img.h;//row 3
						walked = true;
				}
			}
		}
		if(keys[KEY_S]){
			if(rect_dsp.y+rect_dsp.w+speed>=WIN_H){//border
				rect_dsp.y=1;
				my_map.pos.y++;
			}else{
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
		}
		if(keys[KEY_A]){
			if(rect_dsp.x<=0){
				my_map.pos.x--;
				rect_dsp.x=WIN_W-1;
			}else{
				if(
					RoomData[RoomNow][(rect_dsp.x-speed)/TileImgSize/Scale][(rect_dsp.y)/TileImgSize/Scale]!=2&&
					RoomData[RoomNow][(rect_dsp.x-speed)/TileImgSize/Scale][(rect_dsp.y+rect_dsp.h)/TileImgSize/Scale]!=2
					){//block colision
					rect_dsp.x -=speed;
					rect_img.y = rect_img.h;//row 1
					walked = true;
				}
			}
		}
		if(keys[KEY_D]){
			if(rect_dsp.x>=WIN_W){
				rect_dsp.x=1;
				my_map.pos.x++;
			}else{
				if(
				(RoomData[RoomNow][(rect_dsp.x+rect_dsp.w+speed)/TileImgSize/Scale][(rect_dsp.y)/TileImgSize/Scale]!=2&&
				 RoomData[RoomNow][(rect_dsp.x+rect_dsp.w+speed)/TileImgSize/Scale][(rect_dsp.y+rect_dsp.h)/TileImgSize/Scale]!=2)
				||((float)(rect_dsp.x+rect_dsp.w+speed)/TileImgSize/Scale)>16.0){
					rect_dsp.x +=speed;
					rect_img.y = 2*rect_img.h;//row 2
					walked = true;
				}
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

static player my_player;
