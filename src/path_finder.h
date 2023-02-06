#include <SDL2/SDL.h>
#include <stdbool.h>

#include "config.h"
#include "rooms.h"

static bool path[room_w][room_h] = {0};
bool findPath(room *room_ptr,int pos_x,int pos_y,int goal_x,int goal_y){
	
	if(pos_x=goal_x&&pos_y == goal_y){
		return 1;
	}
	
	if(&room_ptr->data[pos_x][pos_y] == 0){
		path[pos_x][pos_y] = 1;
		if(findPath(&room_ptr, pos_x,pos_y+1,goal_x,goal_y) == 1){return 1;}
		if(findPath(&room_ptr, pos_x,pos_y,goal_x,goal_y+1) == 1){return 1;}
		//if(findPath(&room_ptr, pos_x,pos_y-1,goal_x,goal_y) == 1) return 1;
		//if(findPath(&room_ptr, pos_x,pos_y,goal_x,goal_y-1) == 1) return 1;
		path[pos_x][pos_y] = 0;
	}
}
