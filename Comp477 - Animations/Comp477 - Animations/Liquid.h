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

	//vector<GLfloat> localVertices;
	//vector<GLuint> localIndices;
	//vector<GLfloat> localNormals;

	glm::vec3 force;

public:
	Liquid(glm::vec3 cameraPosition);

	/*void updateLiquid();*/
	void sortParticles();

	//vector<GLfloat>* getVertices();
	//vector<GLfloat>* getNormals();

	static vector<vec3> getPositions();
	static vector<vec4> getForcesData();
	static int getNumParticles();
	static void setPressureDesity(int id, float density, float pressure);
	static void setPositionVelocity(int id, vec3 pos, vec3 speed);

	vector<Particle*> particles;
};
