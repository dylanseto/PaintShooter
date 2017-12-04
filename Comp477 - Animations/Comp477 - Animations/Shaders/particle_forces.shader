#version 330 core

// Vertex Shader Input
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in float par_ID;
layout(location = 3) in vec3 speed;
layout(location = 4) in float pressure;
layout(location = 5) in float density;
layout(location = 6) in vec3 normal;

// Particle Constants
#define PARTICLE_NEIGHBOUR_DISTANCE 0.5f
#define MASS 0.02f
#define NRT 5
#define PI 3.14159265

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
	for (int i = 0; i != num_particles; i++)
	{
		if (i == par_ID) continue;

		// 3*i, 3*i+1, 3*i+2
		vec4 ppos = texelFetch(particles, 3*i);
		vec3 pos = vec3(ppos.x, ppos.y, ppos.z);
		vec4 ppressure = texelFetch(particles, 3 * i+1);
		float npressure = ppressure.x;
		vec4 pdensity = texelFetch(particles, 3 * i + 1);
		float ndensity = ppressure.x;

		if (distance(pos, position) >= PARTICLE_NEIGHBOUR_DISTANCE)
		{
			continue;
		}
		vev3 dif = position - pos;
		float norm = sqrt(pow(dif.x, 2) + pow(dif.y, 2) + pow(dif.z, 2));
		vec3 gradientWeight = (45/(PI*pow(PARTICLE_NEIGHBOUR_DISTANCE,6)))*(dif/norm)*pow(PARTICLE_NEIGHBOUR_DISTANCE-norm,2);
		pressureForce += ((pressure + npressure) / 2)*(0.02 / ndensity)*gradientWeight;
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