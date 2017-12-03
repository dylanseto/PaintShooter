#include "Liquid.h"
#include <functional>


int Liquid::NUM_PARTICLES = 0;
multimap<int, Particle*> Liquid::globalParticleMap;

// Special floor function
// floors to 0.5 steps
float specialFloor(float x)
{
	float d = x - (int)x;
	if (d > 0.5) d -= 0.5;
	if (d < 0.3)
	{
		return (floor((x * 2) + 0.5) / 2);
	}
	else if (d == 0.5 || d == 0)
	{
		return x;
	}
	else
	{
		return (floor((x * 2) - 0.5) / 2);
	}
}

Liquid::Liquid()
{

	for (float r = 0; r <= 1.0f; r += 1)
	{
		int num = 50;
		float angle1 = 0.0f;
		float angle = 2 * glm::pi<float>() / (num);

		if (r != 0)
		{
			for (int i = 0; i <= num; i++)
			{
				float x = r * cos(angle1);
				float y = r * sin(angle1);
				float z = 0;
				int spans = 50;
				GLfloat spanDegree = (2 * glm::pi<GLfloat>()) / (GLfloat)spans;

				for (int k = 0; k != spans; k++)
				{
					//glm::rot
					Particle * particle = new Particle();
					particle->id = NUM_PARTICLES;
					particle->pos.x = x;//x*glm::cos(spanDegree*k) - y*glm::sin(spanDegree*k);
					particle->pos.y = y*glm::cos(spanDegree*k) - z*glm::sin(spanDegree*k);
					particle->pos.z = y*glm::sin(spanDegree*k) + z*glm::cos(spanDegree*k);
					particle->life = -1;
					particle->color.r = 1;
					particle->color.g = 0;
					particle->color.b = 0;
					particle->color.a = 1;
					particle->mass = PARTICLE_MASS;
					/*particle->hashKey = to_string(specialFloor(particle->pos.x))
						+ "," + to_string(specialFloor(particle->pos.y))
						+ "," + to_string(specialFloor(particle->pos.z));*/

					particles.push_back(particle);
					//particleNeighbours.insert(std::make_pair(particle->hashKey, particle));
					globalParticleMap.insert(std::make_pair(particle->id, particle));
					NUM_PARTICLES++;
				}
				angle1 += angle;
			}
		}
		else
		{
			Particle * particle = new Particle();
			particle->id = NUM_PARTICLES;
			particle->pos.x = 0;
			particle->pos.y = 0;
			particle->pos.z = 0;
			particle->life = -1;
			particle->color.r = 1;
			particle->color.g = 0;
			particle->color.b = 0;
			particle->color.a = 1;
			particle->mass = PARTICLE_MASS;
			/*particle->hashKey = to_string(specialFloor(particle->pos.x))
				+ "," + to_string(specialFloor(particle->pos.y))
				+ "," + to_string(specialFloor(particle->pos.z));*/

			particles.push_back(particle);
			//particleNeighbours.insert(std::make_pair(particle->hashKey, particle));
			globalParticleMap.insert(std::make_pair(particle->id, particle));
			NUM_PARTICLES++;
		}
	}

	//cout << "num part; " << particles.size() << endl;


	//sort particles
	//sortParticles();

	//Add initial
	for (int i = 0; i != particles.size(); i++)
	{
		localVertices.push_back(particles[i]->pos.x);
		localVertices.push_back(particles[i]->pos.y);
		localVertices.push_back(particles[i]->pos.z);

		localVertices.push_back(particles[i]->color.r);
		localVertices.push_back(particles[i]->color.g);
		localVertices.push_back(particles[i]->color.b);

		//this still goes to position
		localVertices.push_back(particles[i]->id); // chnage to index later

	}
}

Liquid::Liquid(glm::vec3 force)
{
}

void Liquid::updateLiquid()
{
	// Update Particles, physics goes here, update camera distance.

	//Calculate density + pressure
	for (int i = 0; i != particles.size(); i++)
	{
		//calculate density
		particles[i]->density = calculateDensity(particles[i]);
		particles[i]->pressure = calculatePressure(particles[i]);

		//calculate pressure
	}

	//Calculate Forces
	for (int i = 0; i != particles.size(); i++)
	{
		// Pressure force
		vec3 pressureForce = calculatePressureForce(particles[i]);
		// Viscosity 
		vec3 viscosityForce = calculateViscosityForce(particles[i]);
		// Gravity
		vec3 gravityForce = vec3(0, -9.81, 0)*particles[i]->mass;
		// User external force, skip (for now)

		// Sum forces
		vec3 totalForce = pressureForce;
		// Update acceleration
		// Update velocity
		// Check boundaries, update velocity
		// Update positions
	}

	//Update Hash Keys
	//particleNeighbours.clear();
	for (int i = 0; i != particles.size(); i++)
	{
		Particle *particle = particles[i];

		if (!particle->moved) continue;

		multimap<string, Particle*>::iterator it;
		/*for (it = particleNeighbours.lower_bound(particle->hashKey); it != particleNeighbours.end() && it->first != particle->hashKey; it++) {
			if (it->second->id == particle->id) {
				particleNeighbours.erase(it);
			}
		}

		particle->hashKey = to_string(specialFloor(particle->pos.x))
			+ "," + to_string(specialFloor(particle->pos.y))
			+ "," + to_string(specialFloor(particle->pos.z));

		particleNeighbours.insert(std::make_pair(particle->hashKey, particle));*/
	}
	// Sort Particles for render
	// Update vertices, color(if necessary)

	//localVertices.clear();
	//for (int i = 0; i != particles.size(); i++)
	//{
	//	localVertices.push_back(particles[i].pos.x);
	//	localVertices.push_back(particles[i].pos.y);
	//	localVertices.push_back(particles[i].pos.z);

	//	localVertices.push_back(particles[i].color.r);
	//	localVertices.push_back(particles[i].color.g);
	//	localVertices.push_back(particles[i].color.b);
	//	//buffer for Color alpha?
	//}
}

void Liquid::sortParticles()
{
	std::sort(particles.begin(), particles.end());
}

// Getter: Get Local Vertices
vector<GLfloat>* Liquid::getVertices() {
	return &localVertices;
}

float Liquid::calculateDensity(Particle * p)
{
	//typedef multimap<string, Particle*>::iterator MMAPIterator;
	//std::pair<MMAPIterator, MMAPIterator> result = particleNeighbours.equal_range(p->hashKey);
	//float density = 0.0f;
	//for (MMAPIterator it = result.first; it != result.second; it++)
	//{
	//	if (it->second->id == p->id) continue;

	//	Particle *particle = particles[it->second->id];
	//	float dist = distance(particle->pos, p->pos);

	//	if (dist > PARTICLE_NEIGHBOUR_DISTANCE)
	//	{
	//		continue;
	//	}

	//	//cout << "id" << it->second.id << endl;
	//	glm::vec3 dif = p->pos - particle->pos;
	//	float norm = sqrt(pow(dif.x, 2) + pow(dif.y, 2) + pow(dif.z, 2));

	//	float weight = (315 / (64 * glm::pi<float>()*PARTICLE_NEIGHBOUR_DISTANCE))
	//		*glm::pow(PARTICLE_NEIGHBOUR_DISTANCE*PARTICLE_NEIGHBOUR_DISTANCE - norm*norm, 3);

	//	if (weight < 0) // Just double checking
	//	{
	//		continue;
	//	}

	//	density += it->second->mass*weight;

	//	float len = glm::length(particle->pos);
	//}
	//return density;
	return 0;
}

float Liquid::calculatePressure(Particle *p)
{
	float pressure = nrt*p->density;
	return pressure;
}

vec3 Liquid::calculatePressureForce(Particle* p)
{
	//typedef multimap<string, Particle*>::iterator MMAPIterator;
	//std::pair<MMAPIterator, MMAPIterator> result = particleNeighbours.equal_range(p->hashKey);
	//float presssureGradient = 0.0f;
	//vec3 lowPressurePos;
	//float lowPressure = -1;
	//vec3 pressureForce = vec3(0, 0, 0);

	////calculate pressure Gradient and at the same time, calculate lowPressure direction.
	//for (MMAPIterator it = result.first; it != result.second; it++)
	//{
	//	Particle* particle = particles[it->second->id]; //shorthand
	//	glm::vec3 dif = p->pos - particle->pos;

	//	float norm = sqrt(pow(dif.x, 2) + pow(dif.y, 2) + pow(dif.z, 2));
	//	vec3 weightGradient = -1*(45/glm::pi<float>()*pow(PARTICLE_NEIGHBOUR_DISTANCE, 6))*(dif/norm)*pow(PARTICLE_NEIGHBOUR_DISTANCE-norm,2);
	//	vec3 forceComponent = ((p->pressure+particle->pressure)/2)*(particle->mass/particle->density)*weightGradient;

	//	pressureForce += forceComponent;
	//}
	//return pressureForce;
	return vec3();
}

vec3 Liquid::calculateViscosityForce(Particle* p)
{
	//vec3 viscosityForce = vec3(0,0,0);

	//typedef multimap<string, Particle*>::iterator MMAPIterator;
	//std::pair<MMAPIterator, MMAPIterator> result = particleNeighbours.equal_range(p->hashKey);
	//for (MMAPIterator it = result.first; it != result.second; it++)
	//{
	//	Particle* particle = particles[it->second->id]; //shorthand
	//	glm::vec3 difPos = p->pos - particle->pos;
	//	glm::vec3 difVel = particle->speed - p->speed;

	//	float norm = sqrt(pow(difPos.x, 2) + pow(difPos.y, 2) + pow(difPos.z, 2));
	//	float laplacianWeight = 45 / (glm::pi<float>()*pow(PARTICLE_NEIGHBOUR_DISTANCE, 6))*(PARTICLE_NEIGHBOUR_DISTANCE - norm);
	//	vec3 comp = difVel*(particle->mass / particle->density)*laplacianWeight;
	//	viscosityForce += comp;
	//}

	//viscosityForce *= VISCOSITY_KERNEL;
	//return viscosityForce;
	return vec3();
}