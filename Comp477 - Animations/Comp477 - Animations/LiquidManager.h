#pragma once

#include "CommonLibrary.h"
#include "Liquid.h"

class LiquidManager {

	public:
		LiquidManager();

		void createLiquidProjectile();
		void setPaintColor(glm::vec3);

		void update(float deltaTime);

		vector<GLfloat>* getVertices();
		vector<GLfloat>* getNormals();
		bool isEmpty();

		int getNumberOfParticles();
		vector<vec3>* getPositionData();
		vector<vec4>* getForceData();

	private:

		float liquidLifeTime;
		glm::vec3 paintColor;

		// Local Vertices (Pos: x,y,z; Color: r,g,b; ParticleID; Velocity: x,y,z; Pressure; Density)
		vector<GLfloat> localVertices;
		vector<GLfloat> localNormals;

		int numberOfParticles;
		vector<vec3> positionData;
		vector<vec4> forceData;

};