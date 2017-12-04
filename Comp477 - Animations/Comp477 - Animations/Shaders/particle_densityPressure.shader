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
uniform samplerBuffer particles;

// Vertex Shader Output
out float ID;
out float density;
out float pressure;

float calculateDensity()
{
	float density = 0;
	//Iterate thru neighbours
	for (int i = 0; i != 200; i++)
	{
		vec4 text = texelFetch(particles, i);
		vec3 pos = vec3(text.x, text.y, text.z);

		float dist = distance(position, pos); 
		if (dist > PARTICLE_NEIGHBOUR_DISTANCE) // not neighbor
		{
			continue;
		}

		vec3 dif = position - pos;
		float norm = sqrt(pow(dif.x, 2) + pow(dif.y, 2) + pow(dif.z, 2));
		float weight = (315 / (64 * 3.14*PARTICLE_NEIGHBOUR_DISTANCE))
				*pow(PARTICLE_NEIGHBOUR_DISTANCE*PARTICLE_NEIGHBOUR_DISTANCE - norm*norm, 3);

		density += MASS*weight;
	}

	return density;
}

float calculatePressure(float density)
{
	return NRT*density;
}

// Main Method
void main() {
	ID = par_ID;
	density = calculateDensity();
	pressure = calculatePressure(density);
}