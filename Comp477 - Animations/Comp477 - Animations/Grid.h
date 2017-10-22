#pragma once

#include "CommonLibrary.h"

using namespace std;

class Grid {

	public: 
		Grid();

		Grid(GLfloat length, int halfGridSize);

		~Grid();

		vector<GLfloat>* getVertices();
		vector<GLuint>* getIndices();

		int getGridSize();
		glm::vec3 getVertex(int coordX, int coordY);

		void setVertexY(int coordX, int coordY, GLfloat newValue);

		void Grid::printGrid();
		

	private:
		vector<GLfloat> localVertices;
		vector<GLuint> localIndices;
		int gridSize;

};