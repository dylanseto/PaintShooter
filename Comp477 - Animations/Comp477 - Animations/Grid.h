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
		vector<glm::vec3>* getNormals();

		int getGridSize();
		glm::vec3 getVertex(int coordX, int coordY);

		void setVertexY(int coordX, int coordY, GLfloat newValue);

		void Grid::printGrid();
		

	private:
		glm::vec3 vector1;
		glm::vec3 vector2;
		glm::vec3 vectorProduct;

		vector<GLfloat> localVertices;
		vector<GLuint> localIndices;
		vector<glm::vec3> localNormals;

		int gridSize;

};