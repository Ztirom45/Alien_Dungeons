class entity{
	public:
		glm::vec3 pos = glm::vec3(0.0f,-8.0f,-3.0f);//offset form camera pos
		glm::vec3 rot = glm::vec3(0.0f,0.0f,0.0f);//rotation of player model
		mesh player_model;
		int lives = 10;
		float speed = 0.1;
		RectF hitbox = {2,2,0.5,0.5};
		
		
		RectF get_rect(glm::vec2 offset_pos){
			//returns position of x y wh of the model
			return {
				(pos.x-offset_pos.x-hitbox.x-hitbox.w)/2,
				(pos.z-offset_pos.y-hitbox.y-hitbox.h)/2,
				(pos.x-offset_pos.x-hitbox.x+hitbox.w)/2,
				(pos.z-offset_pos.y-hitbox.y+hitbox.h)/2
			};
		};
		
		void setup_model(){
			float W = 20;
			float H = 14;
			std::vector<RectF> texRects = {
				(RectF){0.0f,0.0f,0.5f,10.0f/H},
				(RectF){0.5f,0.0f,0.5f,10.0f/H},
				(RectF){0.0f,10.0f/H,8.0f/W,4.0f/H},
				(RectF){8.0f/W,10.0f/H,4.0f/W,4.0f/H},
				(RectF){12.0f/W,10.0f/H,3.0f/W,3.0f/H},
			};
			
			
			//head
			player_model.add_cube({-0.25,0.4,-0.25},
				{	texRects[0],
					texRects[0],
					texRects[0],
					texRects[1],
					texRects[0],
					texRects[0],

				},{1,1,1,1,1,1},0.5);
			
			//body
			player_model.add_cube({-0.2,0.2,-0.1},
				{	texRects[2],
					texRects[2],
					texRects[3],
					texRects[2],
					texRects[2],
					texRects[3],

				},{1,1,1,1,1,1},0.2,{2.0f,1.0f,1.0f});
			
			//left hand
			player_model.add_cube({-0.35,0.15,0},
				{	texRects[4],
					texRects[4],
					texRects[4],
					texRects[4],
					texRects[4],
					texRects[4],

				},{1,1,1,1,1,1},0.15);
			
			//right Hand
			player_model.add_cube({0.2,0.15,0},
				{	texRects[4],
					texRects[4],
					texRects[4],
					texRects[4],
					texRects[4],
					texRects[4],

				},{1,1,1,1,1,1},0.15);
				
			//left foot
			player_model.add_cube({-0.25,0,-0.05},
				{	texRects[3],
					texRects[3],
					texRects[3],
					texRects[3],
					texRects[3],
					texRects[3],

				},{1,1,1,1,1,1},0.2);
			
			//right foot
			player_model.add_cube({0.05,0,-0.05},
				{	texRects[3],
					texRects[3],
					texRects[3],
					texRects[3],
					texRects[3],
					texRects[3],

				},{1,1,1,1,1,1},0.2);
		};
		
		bool in_wall(glm::vec3 camera_pos,glm::vec2 speed){
			int room_index = my_game_map.room_array_data[(int)my_game_map.pos.x][(int)my_game_map.pos.y];
			RectF Current_Rect = get_rect({camera_pos.x-speed.x,camera_pos.z-speed.y});
			//front
			if(speed.y<0){
				//front left corner
				if(RoomData[room_index][(int)Current_Rect.x][(int)Current_Rect.y]==2){return 1;}
				//front right corner
				if(RoomData[room_index][(int)Current_Rect.w][(int)Current_Rect.y]==2){return 1;}
			}
			
			//left
			if(speed.x<0){
				//left front corner
				if(RoomData[room_index][(int)Current_Rect.x][(int)Current_Rect.y]==2){return 1;}
				//left back corner
				if(RoomData[room_index][(int)Current_Rect.x][(int)Current_Rect.h]==2){return 1;}
			}
			
			//back
			if(speed.y>0){
				//back left corner
				if(RoomData[room_index][(int)Current_Rect.x][(int)Current_Rect.h]==2){return 1;}
				//back right corner
				if(RoomData[room_index][(int)Current_Rect.w][(int)Current_Rect.h]==2){return 1;}
			}
			
			//right
			if(speed.x>0){
				//right front corner
				if(RoomData[room_index][(int)Current_Rect.w][(int)Current_Rect.y]==2){return 1;}
				//right back corner
				if(RoomData[room_index][(int)Current_Rect.w][(int)Current_Rect.h]==2){return 1;}
			}
			return 0;
		};
		
		void update(){
			//lives
			if(lives<=0){
				loop = false;
			}
		};
};
/*
class enemy: public entity{
	public:
		path_finder pf;
		int path_pos = 0;
		vec2i LastPlayerPos = {0,0};
		
		void update_path(RectF PlayerRect){
			//find_path() only if player updated position
			if(PlayerRect.x!=LastPlayerPos.x
			 ||PlayerRect.y!=LastPlayerPos.y){
				
				//path finder stuff
				pf.reset({(int)PlayerRect.x,(int)PlayerRect.y},my_game_map.room_array_data[(int)my_game_map.pos.x][(int)my_game_map.pos.y]);
				pf.find_path((int)PlayerRect.x,(int)PlayerRect.y);
				
				//reset vars
				LastPlayerPos.x = PlayerRect.x;
				LastPlayerPos.y = PlayerRect.y;
				path_pos = 1;
			}
		};
		
		
		void follow_path(){
			glm::vec2 goal = pf.path[path_pos];
			RectF OwnRect = get_rect
			//Down
			if(rect_dsp.y<goal.y){
				if(rect_dsp.y-goal.y<-speed){
					rect_dsp.y +=speed;
				}else{
					rect_dsp.y = goal.y;
				}
				rect_img.y = 0;//row 0
			}
			
			
			//Up
			if(rect_dsp.y>goal.y){
				if(rect_dsp.y-goal.y>speed){
					rect_dsp.y -=speed;
				}else{
					rect_dsp.y = goal.y;
				}
				rect_img.y = 3*rect_img.h;//row 3
			}
			//Right
			if(rect_dsp.x<goal.x){
				if(rect_dsp.x-goal.x<-speed){
					rect_dsp.x += speed;
				}else{
					rect_dsp.x = goal.x;
				}
				rect_img.y = 2*rect_img.h;//row 2
			}
			//Left
			if(rect_dsp.x>goal.x){
				if(rect_dsp.x-goal.x>speed){
					rect_dsp.x -=speed;
				}else{
					rect_dsp.x = goal.x;
				}
				rect_img.y = rect_img.h;//row 1
			}
			
			if(rect_dsp.x==goal.x&&rect_dsp.y==goal.y){
				if(path_pos!=pf.path.size()-1){
					path_pos++;
				}
			}
			
		};
		
		void update(){
			//find path
			
			
			
			//follow_path();
		
			//lives
			if(lives<=0){
				loop = false;
			}
		};

};

static enemy my_enemy;
*/

static entity my_player;

