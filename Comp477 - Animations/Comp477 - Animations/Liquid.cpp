#include "Liquid.h"

Liquid::Liquid()
{

	for (float r = 0; r <= 1.0f; r += 0.05)
	{
		float angle1 = 0.0f;
		float angle = 2 * glm::pi<float>() / (100);

		if (r != 0)
		{
			for (int i = 0; i <= 100; i++)
			{
				float x = r * cos(angle1);
				float y = r * sin(angle1);
				float z = 0;
				int spans = 100;
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

					particles.push_back(particle);
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
			particle.color.g = 0;
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
		//buffer for Color alpha?

		// Adding Textures
		localVertices.push_back(1.0f);
		localVertices.push_back(1.0f);

		// Adding Texture Opacity
		localVertices.push_back(0.0f);
	}

	// Adding Normals
	//int offset = 9;
	for (int i = 0; i < particles.size() / 100; i += 3) {
		vector1 = particles[i + 1].pos - particles[i].pos;
		vector2 = particles[i + 2].pos - particles[i].pos;
		vectorProduct = cross(vector1, vector2);
		localNormals.push_back(normalize(vectorProduct));
	}
}

Liquid::Liquid(glm::vec3 force)
{
}

void Liquid::updateLiquid()
{
	// Update Particles, physics goes here, update camera distance.
	// Sort Particles for render
	// Update vertices, color(if necessary)  indices
}

void Liquid::sortParticles()
{
	std::sort(particles.begin(), particles.end());
}

// Getter: Get Local Vertices
vector<GLfloat>* Liquid::getVertices() {
	return &localVertices;
}

// Getter: Get Local Indices
vector<GLuint>* Liquid::getIndices() {
	return &localIndices;
}

// Getter: Get Local Normals
vector<glm::vec3>* Liquid::getNormals() {
	return &localNormals;
}
