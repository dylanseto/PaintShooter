
#version 330 core

// Vertex Shader Input
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;

// Vertex Shader Output
out vec3 ourColor;

// Uniform Variables 
uniform mat4 pvm;

// Main Method
void main() {
	ourColor = vertexColor;

	gl_PointSize = 20.0f;
	gl_Position = pvm * vec4(position, 1.0f);
}