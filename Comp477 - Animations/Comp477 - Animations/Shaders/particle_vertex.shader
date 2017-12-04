
#version 330 core

// Vertex Shader Input
layout(location = 0) in float par_ID;
layout(location = 1) in vec3 position;
layout(location = 2) in vec3 vertexColor;
layout(location = 3) in vec3 speed;
//layout(location = 4) in float pressure;
//layout(location = 5) in float density;
layout(location = 6) in vec3 normal;

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

	gl_PointSize = 5.0f;
	gl_Position = pvm * vec4(position, 1.0f);
}