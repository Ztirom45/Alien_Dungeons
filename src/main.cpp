//compile: `$ make`

//SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//OGL

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

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

//VAO (vertex array object)
static GLuint VertexArrayObject;

//VBO (vertex buffer object)
static GLuint VertexBufferObject;//positions
static GLuint VertexBufferObject2;//colors
static GLuint VertexBufferObject3;//textures

static std::vector<GLfloat>	vertex_pos = {
	//	x	y	z
		-1,	-1,	-1,
		-1,	1,	-1,
		1,	1,	-1,
		-1,	-1,	-1,
		1,	-1,	-1,
		1,	1,	-1,
		
		-1	,-1,	-1,
		-1	,-1,	1,
		-1	,1,	1,
		-1	,-1,	-1,
		-1	,1,	-1,
		-1	,1,	1,
		
		-1,	-1,	-1,
		-1,	-1,	1,
		1,	-1,	1,
		-1,	-1,	-1,
		1,	-1,	-1,
		1,	-1,	1,
		
		-1,	-1,	1,
		-1,	1,	1,
		1,	1,	1,
		-1,	-1,	1,
		1,	-1,	1,
		1,	1,	1,
		
		1	,-1,	-1,
		1	,-1,	1,
		1	,1,	1,
		1	,-1,	-1,
		1	,1,	-1,
		1	,1,	1,
		
		-1,	1,	-1,
		-1,	1,	1,
		1,	1,	1,
		-1,	1,	-1,
		1,	1,	-1,
		1,	1,	1,
};

static std::vector<GLfloat> vertex_col{
	//   r		g		b
		-1,	-1,	-1,
		-1,	1,	-1,
		1,	1,	-1,
		-1,	-1,	-1,
		1,	-1,	-1,
		1,	1,	-1,
		
		-1	,-1,	-1,
		-1	,-1,	1,
		-1	,1,	1,
		-1	,-1,	-1,
		-1	,1,	-1,
		-1	,1,	1,
		
		-1,	-1,	-1,
		-1,	-1,	1,
		1,	-1,	1,
		-1,	-1,	-1,
		1,	-1,	-1,
		1,	-1,	1,
		
		-1,	-1,	1,
		-1,	1,	1,
		1,	1,	1,
		-1,	-1,	1,
		1,	-1,	1,
		1,	1,	1,
		
		1	,-1,	-1,
		1	,-1,	1,
		1	,1,	1,
		1	,-1,	-1,
		1	,1,	-1,
		1	,1,	1,
		
		-1,	1,	-1,
		-1,	1,	1,
		1,	1,	1,
		-1,	1,	-1,
		1,	1,	-1,
		1,	1,	1,
	};

static std::vector<GLfloat> vertex_tex{
	//  x,	y
		0,	0,
		0,	1,
		1,	1,
		0,	0,
		1,	0,
		1,	1,
		
		0,	0,
		0,	1,
		1,	1,
		0,	0,
		1,	0,
		1,	1,
		
		0,	0,
		0,	1,
		1,	1,
		0,	0,
		1,	0,
		1,	1,
		
		0,	0,
		0,	1,
		1,	1,
		0,	0,
		1,	0,
		1,	1,
		
		0,	0,
		0,	1,
		1,	1,
		0,	0,
		1,	0,
		1,	1,
		
		0,	0,
		0,	1,
		1,	1,
		0,	0,
		1,	0,
		1,	1,
		
	};

#include "shader.hpp"
#include "camera.hpp"
#include "images.hpp"


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
	load_GL_texture();
	
	//print version
	GetOpenGLVersionInfo();
	
	//Enable shuff
	glEnable(GL_TEXTURE_2D);
	
}

void VertexInit(){
	//genereate VAO
	glGenVertexArrays(1,&VertexArrayObject);
	glBindVertexArray(VertexArrayObject);
	
	//generate position VBO at 0
	glGenBuffers(1,&VertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER,VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER,
		vertex_pos.size()*sizeof(GLfloat),
		vertex_pos.data(),
		GL_STATIC_DRAW);
	
	//linking up the position array
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(	0,
							3,//x,y,z
							GL_FLOAT,
							GL_FALSE,
							0,
							(void*)0
	);
		
	//generate color VBO
	glGenBuffers(1,&VertexBufferObject2);
	glBindBuffer(GL_ARRAY_BUFFER,VertexBufferObject2);
	glBufferData(GL_ARRAY_BUFFER,
		vertex_col.size()*sizeof(GLfloat),
		vertex_col.data(),
		GL_STATIC_DRAW);
	
	//linking up the color array
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(	1,
							3,//r,g,b
							GL_FLOAT,//type
							GL_FALSE,//do something with values
							0,
							(void*)0//offset
	);

	//generate texture VBO
	glGenBuffers(1,&VertexBufferObject3);
	glBindBuffer(GL_ARRAY_BUFFER,VertexBufferObject3);
	glBufferData(GL_ARRAY_BUFFER,
		vertex_tex.size()*sizeof(GLfloat),
		vertex_tex.data(),
		GL_STATIC_DRAW);
	
	//linking up the texture array
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(	2,//position
							2,//x,y
							GL_FLOAT,//type
							GL_FALSE,//do something with values
							0,
							(void*)0//offset
	);
	
	//unbind Vertex array
	glBindVertexArray(0);
	//disable attrib arrays
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	
	
}

void events(){//get input events
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

void Input(){//do stuff with keybord inputs
	//transformation
	if(keys[SDLK_w]){
		CameraObject.position.z += 0.1;
	}
	if(keys[SDLK_s]){
		CameraObject.position.z -= 0.1;
	}
	if(keys[SDLK_a]){
		CameraObject.position.x += 0.1;
	}
	if(keys[SDLK_d]){
		CameraObject.position.x -= 0.1;
	}
	if(keys[SDLK_SPACE]){
		CameraObject.position.y -= 0.1;
	}
	if(keys[SDLK_LSHIFT]){
		CameraObject.position.y += 0.1;
	}
	
	CameraObject.rotation.x = 45;
}

void clean(){
	SDL_DestroyWindow(screen);
	
	SDL_Quit();

}

void pre_draw(){
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	
	glViewport(0,0,Win_W,Win_H);
	glClearColor(1.f,1.f,0.f,1.f);
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	
	
	update_textures("img/tiles.png");
	CameraObject.update();
	glUseProgram(ShaderObject.ShaderProgramm);
	
	
}

void draw(){
	glEnable(GL_DEPTH_TEST);
	//send stuff to GPU:
	glBindVertexArray(VertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER,VertexBufferObject);
	
	glDrawArrays(GL_TRIANGLES,0,vertex_pos.size());
	glDisable(GL_DEPTH_TEST);
}

int main(){
	// 1. Setup graphics program 
	init();
	
	// 2. Setup geometry
	VertexInit();
	
	//3. Create shader
	ShaderObject.load_fs_file("src/shader.fs");
	ShaderObject.load_vs_file("src/shader.vs");
	ShaderObject.CreateShader();
	
	//4. main loop
	while(loop){
		events();
		Input();
		
		pre_draw();
		draw();
		
		//camera
		
		//Update Screen
		SDL_GL_SwapWindow(screen);
	}
	
	//5. clean
	clean();
}
