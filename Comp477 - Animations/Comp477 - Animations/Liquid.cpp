#include "Liquid.h"
#include <functional>


int Liquid::NUM_PARTICLES = 0;

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
					particle->hashKey = to_string(floor(particle->pos.x / PARTICLE_NEIGHBOUR_DISTANCE)*PARTICLE_NEIGHBOUR_DISTANCE) 
						+ "," + to_string(floor(particle->pos.y / PARTICLE_NEIGHBOUR_DISTANCE)*PARTICLE_NEIGHBOUR_DISTANCE) 
						+ "," + to_string(floor(particle->pos.z / PARTICLE_NEIGHBOUR_DISTANCE)*PARTICLE_NEIGHBOUR_DISTANCE);

					particles.push_back(particle);
					particleNeighbours.insert(std::make_pair(particle->hashKey, particle));
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
			particle->hashKey = to_string(floor(particle->pos.x / PARTICLE_NEIGHBOUR_DISTANCE)*PARTICLE_NEIGHBOUR_DISTANCE)
				+ "," + to_string(floor(particle->pos.y / PARTICLE_NEIGHBOUR_DISTANCE)*PARTICLE_NEIGHBOUR_DISTANCE)
				+ "," + to_string(floor(particle->pos.z / PARTICLE_NEIGHBOUR_DISTANCE)*PARTICLE_NEIGHBOUR_DISTANCE);

			particles.push_back(particle);
			particleNeighbours.insert(std::make_pair(particle->hashKey, particle));
			NUM_PARTICLES++;
		}
	}

	cout << "num part; " << particles.size() << endl;


	//sort particles
	sortParticles();

	//Add initial
	for (int i = 0; i != particles.size(); i++)
	{
		localVertices.push_back(particles[i]->pos.x);
		localVertices.push_back(particles[i]->pos.y);
		localVertices.push_back(particles[i]->pos.z);

		localVertices.push_back(particles[i]->color.r);
		localVertices.push_back(particles[i]->color.g);
		localVertices.push_back(particles[i]->color.b);

	}
}

Liquid::Liquid(glm::vec3 force)
{
}

void Liquid::updateLiquid()
{
	// Update Particles, physics goes here, update camera distance.
	for (int i = 0; i != particles.size(); i++)
	{
		calculateDensity(particles[i]);
	}

	//Update Hash Keys
	//particleNeighbours.clear();
	for (int i = 0; i != particles.size(); i++)
	{
		Particle *particle = particles[i];

		//if (!particle->moved) continue;

		multimap<string, Particle*>::iterator it;
		for (it = particleNeighbours.lower_bound(particle->hashKey); it != particleNeighbours.end() && it->first != particle->hashKey; it++) {
			if (it->second->id == particle->id) {
				particleNeighbours.erase(it);
			}
		}

		particle->hashKey = to_string(floor(particle->pos.x / PARTICLE_NEIGHBOUR_DISTANCE)*PARTICLE_NEIGHBOUR_DISTANCE)
			+ "," + to_string(floor(particle->pos.y / PARTICLE_NEIGHBOUR_DISTANCE)*PARTICLE_NEIGHBOUR_DISTANCE)
			+ "," + to_string(floor(particle->pos.z / PARTICLE_NEIGHBOUR_DISTANCE)*PARTICLE_NEIGHBOUR_DISTANCE);

		particleNeighbours.insert(std::make_pair(particle->hashKey, particle));
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
	cout << "su" << endl;
	cout << "hash: " << p->hashKey << endl;
	cout << "su" << endl;
	typedef multimap<string, Particle*>::iterator MMAPIterator;
	cout << "ru" << endl;
	std::pair<MMAPIterator, MMAPIterator> result = particleNeighbours.equal_range(p->hashKey);
	cout << "gu" << endl;
	int count = std::distance(result.first, result.second);
	int density = 0.0f;
	for (MMAPIterator it = result.first; it != result.second; it++)
	{
		if (it->second->id == p->id) continue;

		Particle *particle = particles[it->second->id];
		//cout << "id" << it->second.id << endl;
		float norm = sqrt(pow(particle->pos.x, 2) + pow(particle->pos.y, 2) + pow(particle->pos.z, 2));

		float weight = (315 / (64 * glm::pi<float>()*PARTICLE_NEIGHBOUR_DISTANCE))
			*glm::pow(PARTICLE_NEIGHBOUR_DISTANCE*PARTICLE_NEIGHBOUR_DISTANCE - norm*norm, 3);

		density += it->second->mass*weight;

		std::cout << "weight:" << weight << std::endl; //Something weird going on here.
		std::cout << "x:" << particle->pos.x << std::endl;
		std::cout << "y:" << particle->pos.y << std::endl;
		std::cout << "z:" << particle->pos.z << std::endl;
	}
	return 0.0f;
}