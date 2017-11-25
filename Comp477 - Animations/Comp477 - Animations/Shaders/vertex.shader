
#version 330 core

// Vertex Shader Input
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 textureCoord;
layout(location = 3) in float textureOpacity;

// Vertex Shader Output
out vec3 ourColor;
out vec2 outTexCoord;
out float outTextureOpacity;

// Uniform Variables 
uniform mat4 pvm;

// Main Method
void main() {
	ourColor = vertexColor;
	outTexCoord = textureCoord;
	outTextureOpacity = textureOpacity;

	gl_Position = pvm * vec4(position, 1.0f);

}