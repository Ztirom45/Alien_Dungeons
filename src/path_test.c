#include "rooms.h"
#include "path_finder.h"

void main(){
	findPath(1,1,2,2,14,2);
	
	for(int y=0;y<room_h;y++){
		for(int x=0;x<room_w;x++){
			if (room_array[map[1][1]].data[x][y] == 0){
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