//room system liberry
#include "room_data.hpp"

class game_map{
	public:
		int room_array_data[3][3] = {
			{0,1,2},
			{3,4,5},
			{6,7,8}
		};
		
		vec2i pos = {1,1};
		
		void update_chunk(){
			my_chunk.clear();
			for(int x=0;x<=Room_W-1;x++){
				for(int y=0;y<=Room_H-1;y++){
					printf("%d %d\n",x,y);
					Uint8 block_type = RoomData[room_array_data[pos.x][pos.y]][x][y];
					my_chunk.data[x+1][1][y+1] = block_type;
					if(block_type == 2){
						my_chunk.data[x+1][2][y+1] = block_type;
					}
				}
			}
		}
		
};

static game_map my_game_map;
