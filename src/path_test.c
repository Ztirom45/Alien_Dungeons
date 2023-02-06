#include "path_finder.h"

void main(){
	findPath(&room_array[map[1][1]],0,0,10,10);
	
	for(int y=0;y<room_h;y++){
		for(int x=0;x<room_w;x++){
			if (room_array[map[1][1]].data[x][y] == 0){
				printf(" ");
			}else{
				printf("#");
			}
			printf("%d",path[x][y]);
			
		}
		printf("\n");
	}
}
