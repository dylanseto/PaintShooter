#pragma once

#include "Particle.h"
#include "CommonLibrary.h"
#include <map>
using namespace std;
using namespace glm;

class Liquid
{
private:
	static int NUM_PARTICLES;
	static multimap<int, Particle*> globalParticleMap;
	multimap<string, Particle*> particleNeighbours;
	vector<Particle*> particles;
	vector<GLfloat> localVertices;

	glm::vec3 force;

	float calculateDensity(Particle * p);
	float calculatePressure(Particle *p);

	vec3 calculatePressureForce(Particle* p);
	vec3 calculateViscosityForce(Particle* p);

public:
	Liquid();
	Liquid(glm::vec3 force);

	void updateLiquid();
	void sortParticles();

	vector<GLfloat>* getVertices();
};
