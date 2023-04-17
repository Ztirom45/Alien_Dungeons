#version 460 core

//input from vertex shader
in vec4 VertexColorOut;
in vec2 VertexTextureOut;

//output to program
out vec4 color;

//unifor var from program
uniform sampler2D Texture;

void main() {
	//color = VertexColorOut;
	color = texture(Texture, VertexTextureOut);
	
}
