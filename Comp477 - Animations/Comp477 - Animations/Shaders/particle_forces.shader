#version 330 core

// Vertex Shader Input
layout(location = 0) in float par_ID;
layout(location = 1) in vec3 position;
layout(location = 2) in vec3 vertexColor;
layout(location = 3) in vec3 speed;
layout(location = 4) in float pressure;
layout(location = 5) in float density;
layout(location = 6) in vec3 normal;

// Particle Constants
#define PARTICLE_NEIGHBOUR_DISTANCE 0.2f
#define MASS 0.2
#define PI 3.14159265
#define VISCOSITY_CONST 0.001
#define FALSE 0
#define TRUE 1

//uniform vec3 particles[MAX_PARTICLES];
uniform int num_particles;
uniform samplerBuffer particles; //particle positions, pressure, density, velocty
uniform float deltaTime;
uniform vec3 force;
uniform float walls[96];

// Vertex Shader Output
out float ID;
out vec3 newPos;
out vec3 newSpeed;
out float collided;
out vec3 collidedPos;

vec3 gravityForce()
{
	return MASS*vec3(0, -9.81, 0);
}

vec3 pressureForce()
{
	vec3 pressureForce = vec3(0,0,0);
	for (int i = 0; i != num_particles; i++)
	{
		if (i == par_ID) continue;

		vec4 ppos = texelFetch(particles, 4 * i);
		vec3 pos = vec3(ppos.x, ppos.y, ppos.z);
		vec4 ppressure = texelFetch(particles, 4 * i + 1);
		float npressure = ppressure.x;
		vec4 pdensity = texelFetch(particles, 4 * i + 2);
		float ndensity = pdensity.x;


		if (distance(pos, position) >= PARTICLE_NEIGHBOUR_DISTANCE)
		{
			continue;
		}
		//since the difference is really small, I multiply by 100 to do calculations
		//and undo the multiplication at the end
		vec3 dif = (position - pos);
		float norm = sqrt(pow(dif.x, 2) + pow(dif.y, 2) + pow(dif.z, 2));
		//vec3 normalized = dif;

		if (norm == 0) continue;

		vec3 normalized = normalize(dif);

		float comp = ((pressure + npressure) / 2)*(MASS / ndensity);
		vec3 gradientWeight = -1 * (45 / (PI*pow(PARTICLE_NEIGHBOUR_DISTANCE, 6)))*(normalized)*pow(PARTICLE_NEIGHBOUR_DISTANCE - norm, 2);
		pressureForce += comp*gradientWeight*(1/50);
	}

	return pressureForce*-1;
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

		viscosityForce += (nspeed*0.0005)*(MASS / ndensity)*laplacianWeight;
		//break;
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

	bool col = false;
	if (deltaTime > 1)
	{
		newPos = position;
		newSpeed = speed;
		collided = FALSE;
		collidedPos = vec3(10, 10, 10);
		return;
	}
	ID = par_ID;
	vec3 totalForces = gravityForce() + viscosity()+force;
	vec3 acc = totalForces / MASS;

	//highp int i = int(par_ID);
	vec3 curSpeed = totalForces*deltaTime;
	vec3 curPos = position + curSpeed*deltaTime;
	vec3 s = curSpeed;

	if (curPos.y < 0) //intersects with plane.
	{
		s = -1 * curSpeed * 0.5;
		col = true;
	}

	for (int k = 0; k != 16; k++)
	{
		float minX = walls[6*k];
		float maxX = walls[6 * k+1];
		float minY = walls[6 * k+2];
		float maxY = walls[6 * k+3];
		float minZ = walls[6 * k+4];
		float maxZ = walls[6 * k+5];

		if ((position.x >= minX && position.x <= maxX)
			&& (position.y >= minY && position.y <= maxY)
			&& (position.z >= minZ && position.x <= maxZ))
		{
			//We hit a wall, we can stop.
			s = -1 * curSpeed * 0.5;
			col = true;
			//collided = TRUE;
			//collidedPos = curPos;
			break;
		}
	}
	vec4 pspeed = texelFetch(particles, 4 * int(par_ID) + 3);
	vec3 nspeed = vec3(pspeed.x, pspeed.y, pspeed.z);
	newPos = position + s*deltaTime;
	newSpeed = s;

	if (col)
	{
		collided = TRUE;
		collidedPos = position;
		return;
	}
	else
	{
		collided = FALSE;
		collidedPos = position;
		return;
	}

	//vec4 ppos = texelFetch(particles, 4*i+2);
	//newSpeed = s; // temp
}