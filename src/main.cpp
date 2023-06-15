/*
compile:	`$ make`
run:		`./main`
*/

//SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//GLAD
#include <glad/glad.h>

//GLM
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/gtx/string_cast.hpp>

//STD
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <dirent.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>




//config
#define Win_W 1024
#define Win_H 780

//static vars
static bool loop = true;
static bool keys[1073741824] = {0};//(2^30)

//Win vars
static SDL_Window* screen;
static SDL_GLContext GLContext;

//texutres_set: textures[string name] = Gluint data
static std::map<std::string, GLuint> textures;

//include stuff
#include "config.hpp"
#include "types.hpp"
#include "images.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "shader_models.hpp"
#include "block_types.hpp"
#include "chunk.hpp"
#include "rooms.hpp"
#include "path_finder.hpp"
#include "player.hpp"

//cout OpenGL version information
void GetOpenGLVersionInfo(){
	std::cout << "Vendor:				" << glGetString(GL_VENDOR) <<"\n";
	std::cout << "Renderer:			" << glGetString(GL_RENDERER) <<"\n";
	std::cout << "Version:			" << glGetString(GL_VERSION) <<"\n";
	std::cout << "Shading Language:		" << glGetString(GL_SHADING_LANGUAGE_VERSION) <<"\n";
}

void init(){
	//init stuff
	SDL_Init(SDL_INIT_VIDEO);

	//gl Atributs
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);//24bit DepthBuffer
	
	//create open gl window
	screen = SDL_CreateWindow("SDL+OGL",0,32,Win_W,Win_H,SDL_WINDOW_OPENGL);
	
	//create ogl context
	GLContext = SDL_GL_CreateContext(screen);
	
	//init glad lib
	if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
		std::cout << "can't init glad\n";
		exit(1);
	}
	
	//load image
	load_GL_textures();
	
	//print version
	GetOpenGLVersionInfo();
	
	//Enable shuff
	glEnable(GL_TEXTURE_2D);
	
	//setup player
	my_player.setup_model();
	my_player.player_model.texture = "img/Alien.png";
	
	//setup enemy
	my_enemy.setup_model();
	my_enemy.player_model.texture = "img/Alien2.png";
	my_enemy.init();
	
	//setup map
	my_game_map.init();
	

}

//get input events
void events(){
		//events
		SDL_Event event;
		const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					loop = false;
					break;
				case SDL_KEYDOWN:
					keys[event.key.keysym.sym] = true;
					break;
				case SDL_KEYUP:
					keys[event.key.keysym.sym] = false;
					break;
				default:
					break;
			}
		}
}

//do stuff with keybord inputs
void Input(){
	//transformation of camera
	//and player rotation
	glm::vec3 keys_vector = {0.0f,0.0f,0.0f};
	glm::vec3 direction(0.0f);
	float angle;
	
	
	if(keys[SDLK_w]){
		keys_vector.z += 1;
	}
	if(keys[SDLK_s]){
		keys_vector.z -= 1;
	}
	if(keys[SDLK_a]){
		keys_vector.x += 1;
	}
	if(keys[SDLK_d]){
		keys_vector.x -= 1;
	}
	
	
	//normalize the vector only if the retun insn't -nan
	if(keys_vector.x!=0||keys_vector.y!=0||keys_vector.z!=0){
		//callculates direction via normalising the vector
		direction = glm::normalize(keys_vector);
		//calculate the angle of the player
		angle = glm::degrees(atan2(direction.z,-direction.x));
		my_player.rot.y = angle+90;
	}
	
	//cheak for wallcolition seperate on the x and y axe
	if(my_player.in_wall(CameraObject.position,{-direction.x*my_player.speed,0.0f})){
		direction.x = 0;
	}
	
	if(my_player.in_wall(CameraObject.position,{0.0f,-direction.z*my_player.speed})){
		direction.z = 0;
	}
	
	//update position of the player and the camera
	CameraObject.move(direction,my_player.speed);
	
	CameraObject.rotation.x = 70;
}

//cleanup memory (TODO)
void clean(){
	SDL_DestroyWindow(screen);
	SDL_Quit();

}

//game updates
void update(){
	//key events
	events();
	
	//update player
	Input();
	my_player.update();
	my_enemy.update();
}

//frame updates
void pre_draw(){
	//setup mesh
	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	
	glViewport(0,0,Win_W,Win_H);
	glClearColor(1.f,1.f,0.f,1.f);
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	
	
}


int main(){
	// 1. Setup graphics program 
	init();
	
	// 2. Setup geometry (setup method definitely doesn't work the right way TODO)
	my_player.player_model.setup_mesh();
	my_mesh.setup_mesh();
	my_enemy.player_model.setup_mesh();
	my_mesh.setup_mesh();
	my_player.player_model.setup_mesh();
	
	//3. Create shader
	ShaderObject.load_fs_file("src/shader.fs");
	ShaderObject.load_vs_file("src/shader.vs");
	ShaderObject.CreateShader();
	
	//4. main loop
	while(loop){
		
		update();
		
		
		pre_draw();
		
		glEnable(GL_DEPTH_TEST);
		
		//draw player
		
		update_textures(my_player.player_model.texture);
		CameraObject.update();
		
		
		ShaderModelObject.position = glm::vec3(
			my_player.pos.x-CameraObject.position.x,
			my_player.pos.y-CameraObject.position.y,
			my_player.pos.z-CameraObject.position.z);
		
		ShaderModelObject.rotation = my_player.rot;
		ShaderModelObject.update();
		my_player.player_model.draw();
		
		
		//draw enemy
		update_textures(my_enemy.player_model.texture);
		CameraObject.update();
		
		ShaderModelObject.position = glm::vec3(
			my_enemy.pos.x,
			my_enemy.pos.y,
			my_enemy.pos.z);
		
		ShaderModelObject.rotation = my_enemy.rot;
		ShaderModelObject.update();
		my_enemy.player_model.draw();
		
		
		//draw room
		update_textures(my_mesh.texture);
		CameraObject.update();
		ShaderModelObject.position = {0,0,0};
		ShaderModelObject.rotation = {0,0,0};
		ShaderModelObject.update();
		my_mesh.draw();
		
		glDisable(GL_DEPTH_TEST);

		glUseProgram(ShaderObject.ShaderProgramm);
		
		//Update Screen
		SDL_GL_SwapWindow(screen);
	}
	
	//5. clean
	clean();
}
