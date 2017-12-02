
#version 330 core

// Vertex Shader Input
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 normal;

// Vertex Shader Output
flat out vec3 ourColor;
out vec3 ourFragPos;
flat out vec3 ourNormal;

// Uniform Variables 
uniform mat4 pvm;

// Main Method
void main() {
	ourColor = vertexColor;
	ourFragPos = vec3(position);
	ourNormal = vec3(normalize(normal));

	gl_PointSize = 20.0f;
	gl_Position = pvm * vec4(position, 1.0f);
}