
#version 330 core

// Vertex Shader Input
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 collisionPosition;
layout(location = 4) in vec3 collisionColor;

// Vertex Shader Output
out vec3 ourColor;
out vec3 colColor;
out vec3 ourNormal;
out vec3 ourFragPos;
out vec3 colFragPos;

// Uniform Variables 
uniform mat4 pvm;

// Main Method
void main() {
	ourColor = vertexColor;
	ourFragPos = position;
	ourNormal = normal;

	colColor = collisionColor;
	colFragPos = vec3(collisionPosition);

	gl_Position = pvm * vec4(position, 1.0f);
}