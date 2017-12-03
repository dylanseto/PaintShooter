#version 330 core

// Vertex Shader Input
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;

// Vertex Shader Output
out int ID;
out float outValue[2];
out vec3 test;

// Main Method
void main() {
	ID = 2;
	outValue[0] = 3.0f;
	outValue[1] = 4.0f;
	test = vec3(1, 10, 3);
}