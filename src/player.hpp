class player{
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
		void set_rect(RectF Rect,glm::vec2 offset_pos){
			//calculate pos from rect
			pos.x = Rect.x*2+offset_pos.x+hitbox.x+hitbox.w;
			pos.z = Rect.y*2+offset_pos.y+hitbox.y+hitbox.h;
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
				//left back cornere
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

static player my_player;

class enemy: public player{
	public:
		path_finder pf;
		int path_pos = 0;
		glm::vec2 LastPlayerPos = {0,0};
		
		void init(){
			pos = glm::vec3(5.0f,4.0f,5.0f);
			setup_model();
			player_model.texture = "img/Alien.png";
		}
		
		void update_path(RectF PlayerRect){
			//find_path() only if player updated position
			if(PlayerRect.x!=LastPlayerPos.x
			 ||PlayerRect.y!=LastPlayerPos.y){
				
				//reset pathfinder
				pf.reset({(int)PlayerRect.x,(int)PlayerRect.y},my_game_map.room_array_data[(int)my_game_map.pos.x][(int)my_game_map.pos.y]);
				
				//find path
				RectF current_rect = get_rect({0,0});
				
				pf.find_path((int)current_rect.x,(int)current_rect.y);
				
				//reset vars
				LastPlayerPos.x = PlayerRect.x;
				LastPlayerPos.y = PlayerRect.y;
				path_pos = 1;
				
			}
		};
		
		
		void follow_path(void){
			glm::vec2 goal = {(float)pf.path[path_pos].x,(float)pf.path[path_pos].y};//= pf.path_pos[n] dosn't work
			RectF current_rect = get_rect({0,0});
			
			//Down
			if(current_rect.y<goal.y){
				if(current_rect.y-goal.y<-speed){
					current_rect.y +=speed;
				}else{
					current_rect.y = goal.y;
				}
			}
			
			
			//Up
			if(current_rect.y>goal.y){
				if(current_rect.y-goal.y>speed){
					current_rect.y -=speed;
				}else{
					current_rect.y = goal.y;
				}
			}
			
			//Right
			if(current_rect.x<goal.x){
				if(current_rect.x-goal.x<-speed){
					current_rect.x += speed;
				}else{
					current_rect.x = goal.x;
				}
			}
			
			//Left
			if(current_rect.x>goal.x){
				if(current_rect.x-goal.x>speed){
					current_rect.x -=speed;
				}else{
					current_rect.x = goal.x;
				}
			}
			
			if(current_rect.x==goal.x&&current_rect.y==goal.y){
				if(path_pos!=pf.path.size()-1){
					path_pos++;
				}
			}
			
			//printf("e:%f %f\n",current_rect.x,current_rect.y);
			//printf("g:%f %f\n",goal.x,goal.y);
			set_rect(current_rect,{0.0f,0.0f});
		};
		
		void update(void){
			//find path
			update_path(my_player.get_rect({CameraObject.position.x,CameraObject.position.z}));
			follow_path();
		
			//lives
			if(lives<=0){
				loop = false;
			}
		};

};

static enemy my_enemy;



