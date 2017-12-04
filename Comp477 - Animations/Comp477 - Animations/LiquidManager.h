#pragma once

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

	private:

		float liquidLifeTime;
		glm::vec3 paintColor;

		// Local Vertices (Pos: x,y,z; Color: r,g,b; ParticleID; Velocity: x,y,z; Pressure; Density)
		vector<GLfloat> localVertices;
		vector<GLfloat> localNormals;

};