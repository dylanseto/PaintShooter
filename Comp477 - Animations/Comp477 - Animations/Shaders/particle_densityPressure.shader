#version 330 core

// Vertex Shader Input
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;

// Vertex Shader Output
out int ID;
out float outValue[2];
out vec3 test;

float calculateDensity()
{
	float density = 0;
	//Iterate thru neighbours
	for (int i = 0; i != 200; i++)
	{
		density += 20.0f;
	}

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
	return density;
}

float calculatePressure()
{
	return 20;
}

// Main Method
void main() {
	ID = 2;
	outValue[0] = calculateDensity();
	outValue[1] = calculatePressure();
	test = vec3(1, 10, 3);
}