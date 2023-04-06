#version 460 core

layout(location=0) in vec4 position;
layout(location=1) in vec4 vertexColor;

//send stuff to fragment shader

out vec4 VertexColorOut;

uniform mat4 ModelMatrix; //unifor var
uniform mat4 Perspective; //unifor var

void main() {
	VertexColorOut = vertexColor;
	
	mat4 newPerspective =  Perspective;//read only
	newPerspective[0] = vec4(1.0f,1.0f,1.0f,1.0f);
	newPerspective[1] = vec4(1.0f,1.0f,1.0f,1.0f);
	newPerspective[2][0] = 1.0f;
	newPerspective[2][1] = 1.0f;
	newPerspective[2][2] = 1.0f;
	newPerspective[2][3] = Perspective[2][3]*-1.0f;
	newPerspective[2] = vec4(1.0f,1.0f,1.0f,1.0f);
	
	
	vec4 newPosition = newPerspective * ModelMatrix * vec4(position.x,position.y,position.z,1.0f);
	
	gl_Position = newPosition;
}
