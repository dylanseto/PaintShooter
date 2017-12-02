#include "Liquid.h"
#include <functional>


Liquid::Liquid()
{

	for (float r = 0; r <= 1.0f; r += 0.02)
	{
		int num = 100;
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
					Particle particle;
					particle.pos.x = x;//x*glm::cos(spanDegree*k) - y*glm::sin(spanDegree*k);
					particle.pos.y = y*glm::cos(spanDegree*k) - z*glm::sin(spanDegree*k);
					particle.pos.z = y*glm::sin(spanDegree*k) + z*glm::cos(spanDegree*k);
					particle.life = -1;
					particle.color.r = 1;
					particle.color.g = 0;
					particle.color.b = 0;
					particle.color.a = 1;
					particle.mass = 1.0f;
					particle.hashKey = to_string(floor(particle.pos.x / PARTICLE_NEIGHBOUR_DISTANCE)*PARTICLE_NEIGHBOUR_DISTANCE) 
						+ "," + to_string(floor(particle.pos.y / PARTICLE_NEIGHBOUR_DISTANCE)*PARTICLE_NEIGHBOUR_DISTANCE) 
						+ "," + to_string(floor(particle.pos.z / PARTICLE_NEIGHBOUR_DISTANCE)*PARTICLE_NEIGHBOUR_DISTANCE);

					particles.push_back(particle);
					particleNeighbours.insert(std::make_pair(particle.hashKey, particle));
				}
				angle1 += angle;
			}
		}
		else
		{
			Particle particle;
			particle.pos.x = 0;
			particle.pos.y = 0;
			particle.pos.z = 0;
			particle.life = -1;
			particle.color.r = 1;
			particle.color.g = 0.5;
			particle.color.b = 0;
			particle.color.a = 1;
			particle.mass = 1.0f;
		}
	}


	//sort particles
	sortParticles();

	//Add initial
	for (int i = 0; i != particles.size(); i++)
	{
		localVertices.push_back(particles[i].pos.x);
		localVertices.push_back(particles[i].pos.y);
		localVertices.push_back(particles[i].pos.z);

		localVertices.push_back(particles[i].color.r);
		localVertices.push_back(particles[i].color.g);
		localVertices.push_back(particles[i].color.b);

	}
}

Liquid::Liquid(glm::vec3 force)
{
}

void Liquid::updateLiquid()
{
	// Update Particles, physics goes here, update camera distance.

	//Update Hash Keys
	//particleNeighbours.clear();
	//for (int i = 0; i != particles.size(); i++)
	//{
	//	Particle *particle = &particles[i];

	//	particle->hashKey = to_string(floor(particle->pos.x / PARTICLE_NEIGHBOUR_DISTANCE)*PARTICLE_NEIGHBOUR_DISTANCE)
	//		+ "," + to_string(floor(particle->pos.y / PARTICLE_NEIGHBOUR_DISTANCE)*PARTICLE_NEIGHBOUR_DISTANCE)
	//		+ "," + to_string(floor(particle->pos.z / PARTICLE_NEIGHBOUR_DISTANCE)*PARTICLE_NEIGHBOUR_DISTANCE);

	//	particleNeighbours.insert(std::make_pair(particle->hashKey, *particle));
	//}
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