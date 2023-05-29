//room system liberry
#include "room_data.hpp"

class game_map{
	public:
		int room_array_data[3][3] = {
			{0,1,2},
			{3,4,5},
			{6,7,8}
		};
		chunk my_chunks[1][1] = {};
		
		glm::vec2 pos = {1.0f,1.0f};
		
		void update_chunk(int room_x,int room_y){
			printf("rpb:%f %f\n",pos.x,pos.y);
			my_chunks[room_x][room_y].clear();
			printf("rpa: %f %f\n",pos.x,pos.y);
			for(int x=0;x<=Room_W-1;x++){
				for(int y=0;y<=Room_H-1;y++){//[(int)pos.x+room_x][(int)pos.y+room_y]
					Uint8 block_type = RoomData[room_array_data[1][1]][x][y];
					//add floor everytime
					my_chunk.chunk_data[x+1][1][y+1] = block_type;
					my_chunks[room_x][room_y].chunk_data[x+1][1][y+1] = block_type;
					//if type = wall add to wall blocks
					if(block_type == 2){
						my_chunk.chunk_data[x+1][2][y+1] = block_type;
						my_chunk.chunk_data[x+1][3][y+1] = block_type;
						my_chunks[room_x][room_y].chunk_data[x+1][2][y+1] = block_type;
						my_chunks[room_x][room_y].chunk_data[x+1][3][y+1] = block_type;
					}
				}
			}
			my_chunks[room_x][room_y].add_to_mesh();
		};
		
		void update(){
			update_chunk(0,0);
			
		};
		
		void init(){
			pos = {1.0f,1.0f};
			printf("rp1: %f %f\n",pos.x,pos.y);
			update();
		};
		

};

static game_map my_game_map;
