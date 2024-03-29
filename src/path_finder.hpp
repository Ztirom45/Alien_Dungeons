class path_finder{
	public:
		std::vector<glm::vec2> path;
		bool walked[Room_W][Room_W] = {0};//room tiles witch have been walked
		glm::vec2 goal = {0,0};
		int (*room_pointer)[Room_W][Room_W];
		int room_now = 0;//rooms[room_now] to read walls
		
		void reset(glm::vec2 new_goal,int new_room_now){
			goal = new_goal;
			room_now = new_room_now;
			path.resize(0);
			//reset walked
			for(int x=0;x<Room_W;x++){
				for(int y=0;y<Room_H;y++){
					walked[x][y] = 0;
				}
			}
		};
		
		
		void print_walked(){//debug: print walked tiles
			for(int y=0;y<Room_H;y++){
				for(int x=0;x<Room_W;x++){
					printf("%d",walked[x][y]);
					
					if(x==goal.x&&y==goal.y){
						printf("X");
					}else if(RoomData[room_now][x][y]!=2){
						printf(" ");
					}else{
						printf("#");
					}
				}
				printf("\n");
			}
		};
		
		void add(glm::vec2 val){//add position to path
			path.resize(path.size()+1);
			path[path.size()-1] = val;
		}
		void remove(){//remove position from path
			path.resize(path.size()-1);
		}
		
		bool find_path(int x,int y){
			//checks if this feld is insite the array
			if(x<0||y<0||x>=Room_W||y>=Room_H){
				return 0;
			}
			//checks if this feld was visited by the pathfinder
			if(walked[x][y]){
				return 0;
			}
			walked[x][y] = true;
			


			//check if this is a wall
			if(RoomData[room_now][x][y]==2){
				return 0;
			}
			
			//add pos to path
			add({x,y});
			//checks if this is the goal
			if(x==goal.x&&y==goal.y){
				return 1;
			}

			
			
			//select direction witch will be cheacked first to 1/-1
			int Xplus = (goal.x>x)*2-1;
			int Yplus = (goal.y>y)*2-1;
			
			//run findpath LEFT RIGHT UP DOWN
			if(abs(goal.x-x)>abs(goal.y-y)){
				if(find_path(x+Xplus,y		)){return 1;}
				if(find_path(x		,y+Yplus)){return 1;}
				if(find_path(x-Xplus,y		)){return 1;}
				if(find_path(x		,y-Yplus)){return 1;}
			}else{
				if(find_path(x		,y+Yplus)){return 1;}
				if(find_path(x+Xplus,y		)){return 1;}
				if(find_path(x		,y-Yplus)){return 1;}
				if(find_path(x-Xplus,y		)){return 1;}
			}
			return 0;
		};
};
