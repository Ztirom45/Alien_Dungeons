#version 460 core

//input from program
layout(location=0) in vec4 position;
layout(location=1) in vec4 vertexColor;
layout(location=2) in vec2 vertexTexture;






//unifor var from program

uniform mat4 Transformation;
uniform mat4 Rotation; 
uniform mat4 Perspective;

//send stuff to fragment shader
out vec4 VertexColorOut;
out vec2 VertexTextureOut;

void main() {
	VertexColorOut = vertexColor;
	VertexTextureOut = vertexTexture;
	
	
	vec4 newPosition = Perspective * Rotation * Transformation  * vec4(position.x,position.y,position.z,1.0f);
	
	gl_Position = newPosition;
}
