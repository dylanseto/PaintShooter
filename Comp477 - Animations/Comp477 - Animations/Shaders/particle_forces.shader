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
#define VISCOSITY_CONST 3.5

//uniform vec3 particles[MAX_PARTICLES];
uniform int num_particles;
uniform samplerBuffer particles; //particle positions, pressure, density, velocty
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
		vec4 ppos = texelFetch(particles, 4*i);
		vec3 pos = vec3(ppos.x, ppos.y, ppos.z);
		vec4 ppressure = texelFetch(particles, 4 * i+1);
		float npressure = ppressure.x;
		vec4 pdensity = texelFetch(particles, 4 * i + 2);
		float ndensity = pdensity.x;

		//if (ndensity == 0)
		//{
		//	ndensity = 0.01; //cheating
		//}

		if (distance(pos, position) >= PARTICLE_NEIGHBOUR_DISTANCE)
		{
			continue;
		}
		vec3 dif = position - pos;
		float norm = sqrt(pow(dif.x, 2) + pow(dif.y, 2) + pow(dif.z, 2));
		vec3 gradientWeight = (45/(PI*pow(PARTICLE_NEIGHBOUR_DISTANCE,6)))*(dif/norm)*pow(PARTICLE_NEIGHBOUR_DISTANCE-norm,2);
		pressureForce += ((pressure + npressure) / 2)*(0.02 / ndensity)*gradientWeight;
	}

	return pressureForce;
}

vec3 viscosity()
{
	vec3 viscosityForce;
	for (int i = 0; i != num_particles; i++)
	{
		if (i == par_ID) continue;

		vec4 ppos = texelFetch(particles, 4 * i);
		vec3 pos = vec3(ppos.x, ppos.y, ppos.z);
		vec4 pdensity = texelFetch(particles, 4 * i + 2);
		float ndensity = pdensity.x;
		vec4 pspeed = texelFetch(particles, 4 * i+3);
		vec3 nspeed = vec3(pspeed.x, pspeed.y, pspeed.z);

		//if (ndensity == 0)
		//{
		//	ndensity = 0.01; //cheating
		//}

		if (distance(pos, position) >= PARTICLE_NEIGHBOUR_DISTANCE)
		{
			continue;
		}
		vec3 dif = position - pos;
		float norm = sqrt(pow(dif.x, 2) + pow(dif.y, 2) + pow(dif.z, 2));
		float laplacianWeight = (45 / (PI*pow(PARTICLE_NEIGHBOUR_DISTANCE, 6)))*(PARTICLE_NEIGHBOUR_DISTANCE - norm);

		viscosityForce += (nspeed - speed)*(MASS / ndensity)*laplacianWeight;
	}

	return viscosityForce*VISCOSITY_CONST;
}

//vec3 surfaceTension()
//{
//	vec3 surfaceTension;
//	for (int i = 0; i != num_particles; i++)
//	{
//	}
//	return vec3(0, 0, 0);
//}

// Main Method
void main() {
	ID = ndensity;
	vec3 totalForces = gravityForce() + pressureForce() + viscosity();
	vec3 acc = totalForces / MASS;

	newPos = position + speed*deltaTime;
	newSpeed = speed + acc*deltaTime;
}