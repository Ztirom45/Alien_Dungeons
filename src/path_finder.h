#include <SDL2/SDL.h>
#include <stdbool.h>

#include "config.h"
#include "cvec.h"

static int path_len = 0;
static vec2i path[room_w*room_h] = {0};
static bool walked[room_w][room_h] = {0};
static bool path_finder_succes = 0;

bool findPath(int room_x,int room_y,int pos_x,int pos_y,int goal_x,int goal_y){
	
	
	if(pos_x==goal_x&&pos_y == goal_y){
		path_len++;
		path[path_len].x = pos_y;
		path[path_len].y = pos_x;
		path_finder_succes = 1;
		printf("reached\n");
		return 1;
	}
	if(room_array[map[room_x][room_y]].data[pos_x][pos_y]==0&&pos_x<room_w&&pos_y<room_h&&pos_x>=0&&pos_y>=0){
		printf("%d\n",room_array[map[room_y][room_x]].data[pos_x][pos_y]);

		
		path_len++;
		path[path_len].x = pos_x;
		path[path_len].y = pos_y;
		walked[pos_x][pos_y] = 1;
		if(abs(pos_x-goal_x)<abs(pos_y-goal_y)){
			if(walked[pos_x][pos_y+1]==0) if(findPath(room_x,room_y, pos_x,pos_y+1,goal_x,goal_y) == 1){return 1;}
			if(walked[pos_x+1][pos_y]==0) if(findPath(room_x,room_y, pos_x+1,pos_y,goal_x,goal_y) == 1){return 1;}
			if(walked[pos_x][pos_y-1]==0) if(findPath(room_x,room_y, pos_x,pos_y-1,goal_x,goal_y) == 1){return 1;}
			if(walked[pos_x-1][pos_y]==0) if(findPath(room_x,room_y, pos_x-1,pos_y,goal_x,goal_y) == 1){return 1;}
		}else{
			
			if(walked[pos_x+1][pos_y]==0) if(findPath(room_x,room_y, pos_x+1,pos_y,goal_x,goal_y) == 1){return 1;}
			if(walked[pos_x][pos_y+1]==0) if(findPath(room_x,room_y, pos_x,pos_y+1,goal_x,goal_y) == 1){return 1;}
			if(walked[pos_x-1][pos_y]==0) if(findPath(room_x,room_y, pos_x-1,pos_y,goal_x,goal_y) == 1){return 1;}
			if(walked[pos_x][pos_y-1]==0) if(findPath(room_x,room_y, pos_x,pos_y-1,goal_x,goal_y) == 1){return 1;}
		}
		path_len--;
		
	}else{
		return 0;
	}
}
