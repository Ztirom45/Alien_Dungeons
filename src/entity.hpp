class entity{
	public:
		SDL_Rect rect_dsp;	//size and pos on display
		SDL_Rect rect_img;	//pixel positions in images
		
		std::string costume;//texture array
		int lives = 10;
		int speed = 2;
		
		int AnimationFrame = 0;//tick Counter
		bool walked = false;//true if the player walked
		
		path_finder pf;
		int path_pos = 0;
		
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
		rect_dsp.x = 2*256;
		rect_dsp.y = 2*256;
		rect_img.x = 0;
		rect_img.y = 0;
		update_texture(new_costume,{0,0});
	};
	
	void draw(){
		SDL_RenderCopy(rend,textures[costume],&rect_img, &rect_dsp);
	};
	
	void follow_path(){
		vec2i goal = pf.path[path_pos];
		goal.x *= Scale*TileImgSize;
		goal.y *= Scale*TileImgSize;
		
		walked = false;
		
		//Down
		if(rect_dsp.y<goal.y){
			if(rect_dsp.y-goal.y<-speed){
				rect_dsp.y +=speed;
			}else{
				rect_dsp.y = goal.y;
			}
			rect_img.y = 0;//row 0
			walked = true;
		}
		
		
		//Up
		if(rect_dsp.y>goal.y){
			if(rect_dsp.y-goal.y>speed){
				rect_dsp.y -=speed;
			}else{
				rect_dsp.y = goal.y;
			}
			rect_img.y = 3*rect_img.h;//row 3
			walked = true;
		}
		//Right
		if(rect_dsp.x<goal.x){
			if(rect_dsp.x-goal.x<-speed){
				rect_dsp.x += speed;
			}else{
				rect_dsp.x = goal.x;
			}
			rect_img.y = 2*rect_img.h;//row 2
			walked = true;
		}
		//Left
		if(rect_dsp.x>goal.x){
			//printf("hi %d %d\n",rect_dsp.x,goal.x);
			if(rect_dsp.x-goal.x>speed){
				rect_dsp.x -=speed;
			}else{
				rect_dsp.x = goal.x;
			}
			rect_img.y = rect_img.h;//row 1
			walked = true;
		}
		
		//printf("%d %d\n",rect_dsp.x,rect_dsp.y);
		if(rect_dsp.x==goal.x||rect_dsp.y==goal.y){
			if(path_pos==pf.path.size()-1){
				path_pos++;
			}
		}
		
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
		//find path
		path_pos = 1;
		pf.reset({my_player.rect_dsp.x/Scale/TileImgSize,my_player.rect_dsp.y/Scale/TileImgSize},my_map.room_array_data[my_map.pos.x][my_map.pos.y]);
		if(pf.find_path(rect_dsp.x/Scale/TileImgSize,rect_dsp.y/Scale/TileImgSize)){
			//pf.print_walked();
		}
		
		follow_path();
	
		//lives
		if(lives<=0){
			loop = false;
		}
		//animation
		walk(walked);
	}
};

static entity my_enemy;
