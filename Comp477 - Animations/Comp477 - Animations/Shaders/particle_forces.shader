#version 330 core

// Vertex Shader Input
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in float par_id;
layout(location = 3) in vec3 normal;

// Particle Constants
#define PARTICLE_NEIGHBOUR_DISTANCE 0.5f
#define MASS 0.02f

vec3 gravityForce()
{
	return 0.02*vec3(0, -9.81, 0);
}

vec3 pressureForce()
{
	return vec3(0, 0, 0);
}

vec3 viscosity()
{
	return vec3(0, 0, 0);
}

vec3 surfaceTension()
{
	return vec3(0, 0, 0);
}

// Main Method
void main() {
	vec3 totalForces = gravityForce() + pressureForce();
}