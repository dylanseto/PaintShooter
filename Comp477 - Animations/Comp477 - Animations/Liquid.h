#pragma once

#include "Particle.h"
#include "CommonLibrary.h"
#include <unordered_map>
using namespace std;
using namespace glm;

class Liquid
{
private:
	
	unordered_map<string, Particle> particleNeighbours;
	vector<Particle> particles;
	vector<GLfloat> localVertices;

	glm::vec3 force;

public:
	Liquid();
	Liquid(glm::vec3 force);

	void updateLiquid();
	void sortParticles();

	vector<GLfloat>* getVertices();
};
