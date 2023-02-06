#include <SDL2/SDL.h>
#include <stdbool.h>

#include "config.h"
#include "rooms.h"

static bool path[room_w][room_h] = {0};
static bool walked[room_w][room_h] = {0};

bool findPath(int room_x,int room_y,int pos_x,int pos_y,int goal_x,int goal_y){
	if(pos_x==goal_x&&pos_y == goal_y){
		printf("reached\n");
		return 1;
	}
	//printf("%u\n",&room_ptr->data[0][0]);
	if(room_array[map[room_y][room_x]].data[pos_x][pos_y]==0&&pos_x<room_w&&pos_y<room_h&&pos_x>=0&&pos_y>=0){
		path[pos_x][pos_y] = 1;
		walked[pos_x][pos_y] = 1;
		if(walked[pos_x][pos_y+1]==0) if(findPath(room_y,room_y, pos_x,pos_y+1,goal_x,goal_y) == 1){return 1;}
		if(walked[pos_x+1][pos_y]==0) if(findPath(room_y,room_y, pos_x+1,pos_y,goal_x,goal_y) == 1){return 1;}
		if(walked[pos_x][pos_y-1]==0) if(findPath(room_y,room_y, pos_x,pos_y-1,goal_x,goal_y) == 1){return 1;}
		if(walked[pos_x-1][pos_y]==0) if(findPath(room_y,room_y, pos_x-1,pos_y,goal_x,goal_y) == 1){return 1;}
		path[pos_x][pos_y] = 0;
	}else{
		return 0;
	}
}
