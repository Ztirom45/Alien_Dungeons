class player{
	public:
		SDL_Rect rect_dsp;	//size and pos on display
		SDL_Rect rect_img;	//pixel positions in images
		std::string costume;//texture array
		int lives = 10;
		int speed = 10;
		
	
	void update_texture(std::string new_costume,vec2i pos){
		if(costume != new_costume){
			costume = new_costume;
			SDL_QueryTexture(textures[costume], NULL, NULL, &rect_img.w, &rect_img.h);
			rect_img.w = rect_img.w/Map_W;
			rect_img.h = rect_img.h/Map_H;
			rect_img.x = pos.x*Map_W;
			rect_img.x = pos.y*Map_H;
			
			rect_dsp.w = rect_img.w*Scale;
			rect_dsp.h = rect_img.h*Scale;
			
			
		}
		
	}
	
	void init(std::string new_costume){
		rect_dsp.x = 0;
		rect_dsp.y = 0;
		rect_img.x = 0;
		rect_img.y = 0;
		update_texture(new_costume,{0,0});
	};
	
	void draw(){
		SDL_RenderCopy(rend,textures[costume],&rect_img, &rect_dsp);
	};
	
	void update(){
		//control
		if(keys[KEY_W]){
			if(rect_dsp.y<=0){
				rect_dsp.y=WIN_H-1;
				my_map.pos.y-=1;
				//my_map.pos.y
			}else{
			rect_dsp.y -=speed;
			}
		}
		if(keys[KEY_S]){
			if(rect_dsp.y>=WIN_H){
				rect_dsp.y=1;
				my_map.pos.y++;
			}else{
				rect_dsp.y +=speed;
			}
		}
		if(keys[KEY_A]){
			if(rect_dsp.x<=0){
				my_map.pos.x--;
				rect_dsp.x=WIN_W-1;
			}else{
				rect_dsp.x -=speed;
			}
		}
		if(keys[KEY_D]){
			if(rect_dsp.x>=WIN_W){
				rect_dsp.x=1;
				my_map.pos.x++;
			}else{
				rect_dsp.x +=speed;
			}
		}
		
		//lives
		if(lives<=0){
			loop = false;
		}
	}
};

static player my_player;
