#define ChunkSizeX 2+Room_W
#define ChunkSizeY 4
#define ChunkSizeZ 2+Room_H
#define ChunkViewCount 1

//data of chunks
//Uint8 chunks_data[(ChunkViewCount*2+1)*(ChunkViewCount*2+1)][ChunkSizeX][ChunkSizeY][ChunkSizeZ] = {0};

class chunk{
	public:
		//possition of chunk in relation to the player
		glm::vec2 c_pos = {2,2};
		//chunk data pointer 
		Uint8 chunk_data[ChunkSizeX][ChunkSizeY][ChunkSizeZ] = {0};
		
		
		void clear(){
			for(int x=0;x<ChunkSizeX;x++){
				for(int y=0;y<ChunkSizeY;y++){
					for(int z=0;z<ChunkSizeZ;z++){
						chunk_data[x][y][z] = 0;
					}
				}
			}
		};
		
		
		void add_to_mesh(){
			for(int x=1;x<Room_W+1;x++){
				for(int y=0;y<ChunkSizeY;y++){
					for(int z=1;z<Room_H+1;z++){
						Uint8 block_type = chunk_data[x][y][z];
						if(block_type!=0){
							my_mesh.add_cube({(float)x+c_pos.x*Room_W,(float)y,(float)z+c_pos.y*Room_H},block_types[block_type-1],{
								chunk_data[x][y][z-1]==0,
								0,//cant see any down site anytyme: should be `data[x][y-1][z]==0` in normal games
								chunk_data[x-1][y][z]==0,
								chunk_data[x][y][z+1]==0,
								chunk_data[x][y+1][z]==0,
								chunk_data[x+1][y][z]==0
							});
						}
					}
				}
			}
		};
};


