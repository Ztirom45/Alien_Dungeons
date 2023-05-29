#define ChunkSizeX 2+Room_W
#define ChunkSizeY 4
#define ChunkSizeZ 2+Room_H

class chunk{
	public:
		Uint8 chunk_data[ChunkSizeX][ChunkSizeY][ChunkSizeZ] = {0};
		void clear(){
			for(int x=0;x<ChunkSizeX;x++){
				for(int y=0;y<ChunkSizeY;y++){
					for(int z=0;z<ChunkSizeZ;z++){
						chunk_data[x][y][z] = 0;
						printf("%d %d %d\n",x,y,z);
					}
				}
			}
		};
		
		void add_to_mesh(){
			for(int x=0;x<ChunkSizeX;x++){
				for(int y=0;y<ChunkSizeY;y++){
					for(int z=0;z<ChunkSizeZ;z++){
						Uint8 block_type = chunk_data[x][y][z];
						if(block_type!=0){
							my_mesh.add_cube({(float)x,(float)y,(float)z},block_types[block_type-1],{
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

chunk my_chunk;
