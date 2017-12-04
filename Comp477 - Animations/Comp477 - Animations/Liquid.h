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

	
	/*vector<GLfloat> localVertices;
	vector<GLfloat> localNormals;*/

	glm::vec3 force;

public:
	Liquid();
	vector<Particle*> particles;

	void sortParticles();

	/*vector<GLfloat>* getVertices();
	vector<GLfloat>* getNormals();*/

	int getParticleCount();

	static vector<vec3> getPositions();
	static vector<vec3> getForcesData();
	static int getNumParticles();
	static void setPressureDesity(int id, float density, float pressure);
};
