/*
https://www.youtube.com/watch?v=sXbqwzXtecE&list=PLvv0ScY6vfd9zlZkIIqGDeG5TUWswkMox&index=10
32:42

no graphical output 
*/
//SDL
#include <SDL2/SDL.h>
//OGL
#include <glad/glad.h>
//STD
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

//config
#define Win_W 1024
#define Win_H 780

//keys
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_SPACE 32

//static vars
static bool loop = true;
static bool keys[256];//sizeof Uint8 cant't use non letter keys

//Win vars
static SDL_Window* screen;
static SDL_GLContext GLContext;

//VAO (vertex array object)
static GLuint VertexArrayObject;
//VBO (vertex buffer object)
static GLuint VertexBufferObject;

#include "shader.hpp"


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
	
	//print version
	GetOpenGLVersionInfo();
	
}

void VertexInit(){
	//data
	const std::vector<GLfloat> vertex_pos{
	//   x		y	z
		-0.8f,-0.8f,0.0f,//vert1
		-0.8f,0.0f,0.0f,//vert2
		0.0f,-0.8f,0.0f //vert3
	};
	
	//generate VAO
	glGenVertexArrays(1,&VertexArrayObject);
	glBindVertexArray(VertexArrayObject);
	
	//generate VBO
	glGenBuffers(1,&VertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER,VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER,
		vertex_pos.size()*sizeof(GLfloat),
		vertex_pos.data(),
		GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(	0,
							3,//x,y,z
							GL_FLOAT,
							GL_FALSE,
							0,
							(void*)0
	);
	
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	
	
}

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
				if(event.key.keysym.sym<256){keys[event.key.keysym.sym] = true;}
				break;
			case SDL_KEYUP:
				if(event.key.keysym.sym<256){keys[event.key.keysym.sym] = false;}
				break;
			default:
				break;
			}
		}
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
	
	glUseProgram(ShaderObject.ShaderProgramm);
}

void draw(){
	glBindVertexArray(VertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER,VertexBufferObject);
	
	glDrawArrays(GL_TRIANGLES,0,3);
}

int main(){
	init();
	
	VertexInit();
	
	ShaderObject.CreateShader();
	
	while(loop){
		events();
		
		pre_draw();
		draw();
		
		//Update Screen
		SDL_GL_SwapWindow(screen);
	}
	
	clean();
}
