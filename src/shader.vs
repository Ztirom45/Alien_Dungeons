#version 460 core

layout(location=0) in vec4 position;
layout(location=1) in vec4 vertexColor;

//send stuff to fragment shader

out vec4 VertexColorOut;

uniform mat4 Transformation; //unifor var
uniform mat4 Rotation; //unifor var
uniform mat4 Perspective; //unifor var

void main() {
	VertexColorOut = vertexColor;
	
	//
	vec4 newPosition =  Perspective * Rotation * Transformation  * vec4(position.x,position.y,position.z,1.0f);
	
	gl_Position = newPosition;
}
