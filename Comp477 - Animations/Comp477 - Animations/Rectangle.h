#pragma once

#include "CommonLibrary.h"

using namespace std;

class Rectangle
{

public:
	Rectangle();
	Rectangle(GLfloat length, GLfloat height, GLfloat depth);

	vector<GLfloat>* getVertices();
	vector<GLuint>* getIndices();
	vector<glm::vec3>* getNormals();

	GLfloat getLength();
	GLfloat getHeight();
	GLfloat getDepth();

private:
	GLfloat length;
	GLfloat height;
	GLfloat depth;

	glm::vec3 vector1;
	glm::vec3 vector2;
	glm::vec3 vectorProduct;

	vector<GLfloat> localVertices;
	vector<GLuint> localIndices;
	vector<glm::vec3> localNormals;
};