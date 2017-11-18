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

	GLfloat getLength();
	GLfloat getHeight();
	GLfloat getDepth();

private:
	GLfloat length;
	GLfloat height;
	GLfloat depth;

	vector<GLfloat> localVertices;
	vector<GLuint> localIndices;
};