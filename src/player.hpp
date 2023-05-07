class player{
	public:
		glm::vec3 pos = glm::vec3(0.0f,-8.0f,-3.0f);//offset form camera pos
		glm::vec3 rot = glm::vec3(0.0f,0.0f,0.0f);//rotation of player model
		mesh player_model;
		int lives = 10;
		float speed = 0.1;
		RectF hitbox = {2,2,0.5,0.5};
		
		
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
			int x,y;
			//front
			if(speed.y<0){
				
				y = (int)(pos.z-camera_pos.z-hitbox.y-hitbox.h+speed.y)/2;
				//front left corner
				x = (int)(pos.x-camera_pos.x-hitbox.x-hitbox.w+speed.x)/2;
				if(RoomData[room_index][x][y]==2){return 1;}
				
				//front right corner
				x = (int)(pos.x-camera_pos.x-hitbox.x+hitbox.w+speed.x)/2;
				if(RoomData[room_index][x][y]==2){return 1;}
			}
			
			//left
			if(speed.x<0){
				x = (int)(pos.x-camera_pos.x-hitbox.x-hitbox.w+speed.x)/2;
				
				//front left corner
				y = (int)(pos.z-camera_pos.z-hitbox.y-hitbox.h+speed.y)/2;
				if(RoomData[room_index][x][y]==2){return 1;}
				
				//back left corner
				y = (int)(pos.z-camera_pos.z-hitbox.y+hitbox.h+speed.y)/2;
				if(RoomData[room_index][x][y]==2){return 1;}
			}
			
			//back
			if(speed.y>0){
				y = (int)(pos.z-camera_pos.z-hitbox.y+hitbox.h+speed.y)/2;
				
				//front left corner
				x = (int)(pos.x-camera_pos.x-hitbox.x-hitbox.w+speed.x)/2;
				if(RoomData[room_index][x][y]==2){return 1;}
				
				//front right corner
				x = (int)(pos.x-camera_pos.x-hitbox.x+hitbox.w+speed.x)/2;
				if(RoomData[room_index][x][y]==2){return 1;}
			}
			
			//right
			if(speed.x>0){
				x = (int)(pos.x-camera_pos.x-hitbox.x+hitbox.w+speed.x)/2;
				
				//front left corner
				y = (int)(pos.z-camera_pos.z-hitbox.y-hitbox.h+speed.y)/2;
				if(RoomData[room_index][x][y]==2){return 1;}
				
				//back left corner
				y = (int)(pos.z-camera_pos.z-hitbox.y+hitbox.h+speed.y)/2;
				if(RoomData[room_index][x][y]==2){return 1;}
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
