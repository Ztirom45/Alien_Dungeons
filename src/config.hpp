#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

//window
#define WIN_W 1024
#define WIN_H 1024

#define IMAGE_COUNT 1

#define ButtonRes 40//resulution from button image

//room
#define Room_W 16
#define Room_H 16
#define TileImgSize 16
/* Room_W,Room_H*TileImgSize*scale = Win_W,Win_H*/

//texture
#define Map_W 3
#define Map_H 4

#define Scale 4

//Animation
#define AnimationFPS 8//AnimationFrames per secount
#define AnimationFrameCount 3//count of AnimationFrames
