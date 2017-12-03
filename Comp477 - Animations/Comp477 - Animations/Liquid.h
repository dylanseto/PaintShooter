#pragma once

#include "Particle.h"
#include "CommonLibrary.h"
using namespace std;
using namespace glm;

class Liquid
{
private:
	static float NUM_PARTICLES;
	glm::vec3 vector1;
	glm::vec3 vector2;
	glm::vec3 vectorProduct;

	vector<Particle> particles;
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
	vector<GLuint>* getIndices();
	vector<glm::vec3>* getNormals();
};
