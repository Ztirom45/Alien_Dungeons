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
		if(keys[KEY_W]&&rect_dsp.y>0){
			rect_dsp.y -=speed;
		}
		if(keys[KEY_S]&&rect_dsp.y+rect_dsp.h<WIN_H){
			rect_dsp.y +=speed;
		}
		if(keys[KEY_A]&&rect_dsp.x>0){
			rect_dsp.x -=speed;
		}else if(keys[KEY_D]&&rect_dsp.x+rect_dsp.w<WIN_W){
			rect_dsp.x +=speed;
		}
		
		//lives
		if(lives<=0){
			loop = false;
		}
	}
};

static player my_player;
