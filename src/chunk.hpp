#define ChunkSizeX Room_W+2
#define ChunkSizeY 3
#define ChunkSizeZ Room_H+2

class chunk{
	public:
		Uint8 data[ChunkSizeX][ChunkSizeY][ChunkSizeZ] = {0};
		void clear(){
			for(int x=0;x<=ChunkSizeX;x++){
				for(int y=0;y<=ChunkSizeY;y++){
					for(int z=0;z<=ChunkSizeZ;z++){
						data[x][y][z] = 0;
					}
				}
			}
		};
		
		void add_to_mesh(){
			for(int x=0;x<=ChunkSizeX;x++){
				for(int y=0;y<=ChunkSizeY;y++){
					for(int z=0;z<=ChunkSizeZ;z++){
						if(data[x][y][z]!=0){
							my_mesh.add_cube({(float)x,(float)y,(float)z},block_types[data[x][y][z]-1],{1,1,1,1,1,1});
						}
					}
				}
			}
		};
};

chunk my_chunk;
