//room system liberry
#include "room_data.hpp"

//macros for readability
#define RposX (int)(room_x+pos.x)
#define RposY (int)(room_y+pos.y)
#define CurrentChunk my_chunks_ptr[RposX][RposY]

class game_map{
	public:
		int room_array_data[3][3] = {
			{0,1,2},
			{3,4,5},
			{6,7,8}
		};
		chunk *my_chunks_ptr[(ChunkViewCount*2+1)][(ChunkViewCount*2+1)] = {};
		
		
		glm::vec2 pos = {1,1};
		
		void update_chunk(int room_x,int room_y){
			if(RposX>=0 && RposX<=ChunkViewCount*2  &&  RposY>=0 && RposY<=ChunkViewCount*2){
				CurrentChunk->c_pos = {room_x,room_y};
				CurrentChunk->clear();
				
				for(int x=0;x<=Room_W-1;x++){
					for(int y=0;y<=Room_H-1;y++){
						Uint8 block_type = RoomData[room_array_data[RposX][RposY]][x][y];
						//add floor everytime
						CurrentChunk->chunk_data[x+1][1][y+1] = block_type;
						
						CurrentChunk->chunk_data[x+1][1][y+1] = block_type;
						//if type = wall add to wall blocks
						if(block_type == 2){
							CurrentChunk->chunk_data[x+1][2][y+1] = block_type;
							CurrentChunk->chunk_data[x+1][3][y+1] = block_type;
							CurrentChunk->chunk_data[x+1][2][y+1] = block_type;
							CurrentChunk->chunk_data[x+1][3][y+1] = block_type;
						}
					}
				}
			CurrentChunk->add_to_mesh();
			
			}

			
		};
		
		void update(){
			for(int x=-ChunkViewCount;x<=ChunkViewCount;x++){
				for(int y=-ChunkViewCount;y<=ChunkViewCount;y++){
					update_chunk(x,y);
				}
			}
			
		};
		
		void init(){
			//allocate memory to my_chunks_ptr
			for(int y = 0;y<(ChunkViewCount*2+1);y++){
				for(int x = 0;x<(ChunkViewCount*2+1);x++){
					my_chunks_ptr[x][y] = new chunk;
					my_chunks_ptr[x][y]->clear();
				}
			}
			update();

		};
		

};

static game_map my_game_map;
