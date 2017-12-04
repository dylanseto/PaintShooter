#version 330 core

// Vertex Shader Input
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in float par_ID;
layout(location = 3) in vec3 speed;
layout(location = 4) in vec3 normal;

// Particle Constants
#define PARTICLE_NEIGHBOUR_DISTANCE 0.5f
#define MASS 0.02f
#define NRT 5

//uniform vec3 particles[MAX_PARTICLES];
uniform int num_particles;
uniform samplerBuffer particles; //particle positions, pressure, density
uniform float deltaTime;

// Vertex Shader Output
out float ID;
out vec3 newPos;
out vec3 newSpeed;

vec3 gravityForce()
{
	return MASS*vec3(0, -9.81, 0);
}

vec3 pressureForce()
{
	vec3 pressureForce;
	for (int i = 0; i != NUM_PARTICLES; i++)
	{
		if (i == par_ID) continue;

		// 3*i, 3*i+1, 3*i+2
		vec4 ppos = texelFetch(particles, 3*i);
		vec3 pos = vec3(ppos.x, ppos.y, ppos.z);
		vec4 ppressure = texelFetch(particles, 3 * i+1);
		float pressure = ppressure.x;
		vec4 pdensity = texelFetch(particles, 3 * i + 1);
		float density = ppressure.x;

		if (distance(pos, position) >= PARTICLE_NEIGHBOUR_DISTANCE)
		{
			continue;
		}
	}

	return -1*pressureForce;
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
	ID = par_ID;
	vec3 totalForces = gravityForce() + pressureForce();
	vec3 acc = totalForces / MASS;

	//vec3 speed = acc*deltaTime; // TODO : add to old speed.
	//vec3 pos = position + speed*deltaTime;

	newPos = position + speed*deltaTime;
	newSpeed = speed+ acc*deltaTime;
}