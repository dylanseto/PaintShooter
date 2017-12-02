#pragma once

#include "Particle.h"
#include "CommonLibrary.h"
using namespace std;
using namespace glm;

class Liquid
{
private:

	vector<Particle> particles;
	vector<GLfloat> localVertices;
	vector<GLuint> localIndices;

	glm::vec3 force;

public:
	Liquid();
	Liquid(glm::vec3 force);

	void updateLiquid();
	void sortParticles();

	vector<GLfloat>* getVertices();
	vector<GLuint>* getIndices();
};
