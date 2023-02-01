#include "config.h"

static int rx = 1;
static int ry = 1;

typedef struct _room{
	int data[room_w][room_h];
}room;

/*
room +dor pos

t = top
b = button
r = right
l = left

examples:
roomlt =  doors on left and top wall
*/
const room room_tbrl = {{
{1,1,1,1, 1,1,0,0, 0,0,1,1, 1,1,1,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},//  |
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},//--+--
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},//  |
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},

{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,1,1,1, 1,1,0,0, 0,0,1,1, 1,1,1,1}}};

const room room_brl = {{
{1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},//
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},//--+--
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},//  |
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},

{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,1,1,1, 1,1,0,0, 0,0,1,1, 1,1,1,1}}};

const room room_trl = {{
{1,1,1,1, 1,1,0,0, 0,0,1,1, 1,1,1,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},//  |
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},//--+--
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},//
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},

{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1}}};

const room room_tbl = {{
{1,1,1,1, 1,1,0,0, 0,0,1,1, 1,1,1,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,1,1,1, 1,1,0,0, 0,0,1,1, 1,1,1,1}}};

const room room_tbr = {{
{1,1,1,1, 1,1,0,0, 0,0,1,1, 1,1,1,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,1,1,1, 1,1,0,0, 0,0,1,1, 1,1,1,1}}};


const room room_tr = {{
{1,1,1,1, 1,1,0,0, 0,0,1,1, 1,1,1,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},//  |
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},//--+--
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},//  |
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1}}};

const room room_br = {{
{1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},//  |
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},//--+--
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},//  |
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,1,1,1, 1,1,0,0, 0,0,1,1, 1,1,1,1}}};

const room room_tl = {{
{1,1,1,1, 1,1,0,0, 0,0,1,1, 1,1,1,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},//  |
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},//--+--
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},//  |
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1}}};

const room room_bl = {{
{1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},//  |
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},//--+--
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},//  |
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},

{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1},
{1,1,1,1, 1,1,0,0, 0,0,1,1, 1,1,1,1}}};


room room_array[room_count] = {
room_tbrl,//0

room_trl, //1
room_brl, //2
room_tbl, //3
room_tbr,//4

room_tr,//5
room_br,//6
room_tl,//7
room_bl};//8

/*
void setup_array(){
	room room_array[0] = room1;
}*/

int map[map_w][map_h] = {
	{6,2,8},
	{4,0,3},
	{5,1,7}
};

