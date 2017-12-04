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

Liquid::Liquid(glm::vec3 paintColor, ::vec3 force)
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
					if (particle->pos.z <= 0.01f && particle->pos.z > 0) particle->pos.z = 0;
					if (particle->pos.z >= 0.01f && particle->pos.z < 0) particle->pos.z = 0;

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

		//color
		localVertices.push_back(1);
		localVertices.push_back(0);
		localVertices.push_back(0);

		localVertices.push_back(i);

		localVertices.push_back(particles[i]->speed.x);
		localVertices.push_back(particles[i]->speed.y);
		localVertices.push_back(particles[i]->speed.z);

		localVertices.push_back(particles[i]->pressure);
		localVertices.push_back(particles[i]->density);
		//cout << i << endl;

		//cout << "y values: " << particles[i]->pos.y << endl;
		//buffer for Color alpha?
	}
	for (int i = 0; i < particles.size(); i++) {
		normalize(particles[i]->pos);
		localNormals.push_back(particles[i]->pos.x);
		localNormals.push_back(particles[i]->pos.y);
		localNormals.push_back(particles[i]->pos.z);
	}
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
vector<GLfloat>* Liquid::getNormals() {
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

vector<vec4> Liquid::getForcesData()
{
	vector<vec4> data;
	for (int i = 0; i != allParticles.size(); i++)
	{
		data.push_back(vec4(allParticles[i]->pos, 0));//(allParticles[i]->pos);
		//cout << "data Pos: (" << allParticles[i]->pos.x << "," << allParticles[i]->pos.y << "," << allParticles[i]->pos.z << ")" << endl;
		//cout << "pressure" << allParticles[i]->pressure << endl;
		data.push_back(vec4(allParticles[i]->pressure, 0, 0, i));
		data.push_back(vec4(allParticles[i]->density, 0, 0, i));
		data.push_back(vec4(allParticles[i]->speed,i));
	}
	return data;
}

int Liquid::getNumParticles()
{
	return allParticles.size();
}

void Liquid::setPressureDesity(int id, float density, float pressure)
{
	allParticles[id]->density = density;
	allParticles[id]->pressure = pressure;
	//cout << "pressure" << allParticles[id]->pressure << endl;
}

void Liquid::setPositionVelocity(int id, vec3 pos, vec3 speed)
{
	allParticles[id]->pos = pos;
	allParticles[id]->speed = speed;
}
