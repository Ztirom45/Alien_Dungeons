#ifndef CONFIG
#define CONFIG
//window
#define win_w 1024
#define win_h 1024

//images
#define ScaleFactor 4

//tiles
#define Tile_W 64
#define Tile_H 64


//imageMap
#define IMG_MAP_W 3
#define IMG_MAP_H 4

//Alien size
#define Alien_W 10
#define Alien_H 14

//room
#define tile_count 3
#define room_w 16
#define room_h 16

//map
#define room_count 9
#define map_w 3
#define map_h 3

//animation
#define ANIMATION_DELAY_FRAMES 2
#define ANIMATION_FRAMES 5 //count+1(bug)

int Frame_Array[ANIMATION_FRAMES] = {0,10,0,20,0};
int Frame_Now = 0;

#endif
