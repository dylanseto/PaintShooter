#include "Liquid.h"

int Liquid::NUM_PARTICLES = 0;
vector<Particle*> Liquid::allParticles;

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

	for (float r = 0; r <= 1.0f; r += 0.5)
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
					Particle*  particle = new Particle();
					particle->id = NUM_PARTICLES;
					particle->pos.x = x;//x*glm::cos(spanDegree*k) - y*glm::sin(spanDegree*k);
					particle->pos.y = y*glm::cos(spanDegree*k) - z*glm::sin(spanDegree*k);
					particle->pos.z = y*glm::sin(spanDegree*k) + z*glm::cos(spanDegree*k);
					particle->life = -1;
					particle->color.r = 1;
					particle->color.g = 0;
					particle->color.b = 0;
					particle->color.a = 1;
					particle->mass = 1.0f;
					particle->index = vec3(specialFloor(particle->pos.x), specialFloor(particle->pos.y), specialFloor(particle->pos.z));

					particles.push_back(particle);
					allParticles.push_back(particle);
					NUM_PARTICLES++;
				}
				angle1 += angle;
			}
		}
		else
		{
			Particle* particle = new Particle();
			particle->id = NUM_PARTICLES;
			particle->pos.x = 0;
			particle->pos.y = 0;
			particle->pos.z = 0;
			particle->life = -1;
			particle->color.r = 1;
			particle->color.g = 0;
			particle->color.b = 0;
			particle->color.a = 1;
			particle->mass = 1.0f;
			particle->index = vec3(specialFloor(particle->pos.x), specialFloor(particle->pos.y), specialFloor(particle->pos.z));
			particles.push_back(particle);
			allParticles.push_back(particle);

			NUM_PARTICLES++;
		}
	}


	//sort particles
	sortParticles();

	//Add initial
	for (float i = 0; i != particles.size(); i++)
	{
		localVertices.push_back(particles[i]->pos.x);
		localVertices.push_back(particles[i]->pos.y);
		localVertices.push_back(particles[i]->pos.z);

		localVertices.push_back(particles[i]->color.r);
		localVertices.push_back(particles[i]->color.g);
		localVertices.push_back(particles[i]->color.b);

		localVertices.push_back(i);

		localVertices.push_back(particles[i]->speed.x);
		localVertices.push_back(particles[i]->speed.y);
		localVertices.push_back(particles[i]->speed.z);

		localVertices.push_back(particles[i]->pressure);
		localVertices.push_back(particles[i]->density);
		//cout << i << endl;

		//cout << "y values: " << particles[i]->pos.y << endl;
		//buffer for Color alpha?

		// Adding Textures
		//localVertices.push_back(1.0f);
		//localVertices.push_back(1.0f);

		//// Adding Texture Opacity
		//localVertices.push_back(0.0f);
	}

	for (int i = 0; i < particles.size(); i++) {
		localNormals.push_back(normalize(particles[i]->pos));
	}
}

Liquid::Liquid(glm::vec3 force)
{
}

void Liquid::updateLiquid()
{
	//for (float i = 0; i != particles.size(); i++)
	//{
	//	localVertices.push_back(particles[i]->pos.x);
	//	localVertices.push_back(particles[i]->pos.y);
	//	localVertices.push_back(particles[i]->pos.z);

	//	localVertices.push_back(particles[i]->color.r);
	//	localVertices.push_back(particles[i]->color.g);
	//	localVertices.push_back(particles[i]->color.b);

	//	localVertices.push_back(i); // ID

	//	localVertices.push_back(particles[i]->speed.x);
	//	localVertices.push_back(particles[i]->speed.y);
	//	localVertices.push_back(particles[i]->speed.z);

	//	localVertices.push_back(particles[i]->pressure);
	//	localVertices.push_back(particles[i]->density);
	//}

	//for (int i = 0; i < particles.size(); i++) {
	//	localNormals.push_back(normalize(particles[i]->pos));
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

// Getter: Get Local Normals
vector<glm::vec3>* Liquid::getNormals() {
	return &localNormals;
}

vector<vec3> Liquid::getPositions()
{
	vector<vec3> positions;
	for (int i = 0; i != allParticles.size(); i++)
	{
		positions.push_back(allParticles[i]->pos);
	}
	return positions;
}

vector<vec3> Liquid::getForcesData()
{
	vector<vec3> data;
	for (int i = 0; i != allParticles.size(); i++)
	{
		data.push_back(allParticles[i]->pos);
		data.push_back(vec3(allParticles[i]->pressure, 0, 0));
		data.push_back(vec3(allParticles[i]->density, 0, 0));
		data.push_back(allParticles[i]->speed);
	}
	return data;
}

int Liquid::getNumParticles()
{
	return NUM_PARTICLES;
}

void Liquid::setPressureDesity(int id, float density, float pressure)
{
	allParticles[id]->density = density;
	allParticles[id]->density = pressure;
}
