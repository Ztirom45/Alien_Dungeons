#include "rooms.h"
#include "path_finder.h"

void main(){
	findPath(0,1,2,2,14,14);
	
	for(int x=0;x<room_w;x++){
		for(int y=0;y<room_h;y++){
			if (room_array[map[0][1]].data[x][y] == 0){
				printf(" ");
			}else{
				printf("#");
			}
			printf("%d",walked[x][y]);
			
		}
		printf("\n");
	}
	for(int i=0;i<path_len;i++){
		printf("%d %d\n",path[i].x,path[i].y);
	}
}
