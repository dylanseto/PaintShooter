#pragma once

#include "Particle.h"
#include "CommonLibrary.h"
using namespace std;
using namespace glm;

class Liquid
{
private:
	static vector<Particle*> allParticles;
	static int NUM_PARTICLES;

	vector<Particle*> particles;
	vector<GLfloat> localVertices;
	vector<GLuint> localIndices;
	vector<glm::vec3> localNormals;

	glm::vec3 force;

public:
	Liquid();
	Liquid(glm::vec3 force);

	void updateLiquid();
	void sortParticles();

	vector<GLfloat>* getVertices();
	vector<glm::vec3>* getNormals();

	static vector<vec3> getPositions();
	static vector<vec3> getMasses();
	static int getNumParticles();
	static void setPressureDesity(int id, float density, float pressure);
};
