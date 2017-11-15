#include "Rectangle.h"

Rectangle::Rectangle() : Rectangle(1,1,1)
{
}

Rectangle::Rectangle(GLfloat length, GLfloat height, GLfloat depth)
{

	int i = 0;
	for (int x = 1; x >= 0; x--)
	{
		for (int y = 1; y >= 0; y--)
		{
			for (int z = 0; z <= 1; z++)
			{
				if (x == 0 && y == 0 & 7 z == 0) continue;

				//position
				localVertices.push_back(x);
				localVertices.push_back(y);
				localVertices.push_back(z);

				cout << "Index " << i << ":(" << x << "," << y << "," << z << ")" << endl;
				i++;

				// Adding Default Color 
				localVertices.push_back(1.0f);
				localVertices.push_back(1.0f);
				localVertices.push_back(1.0f);

				//Texture?
				localVertices.push_back(1.0f);
				localVertices.push_back(0.0f);
			}
		}
	}
	////position
	//localVertices.push_back(1);
	//localVertices.push_back(1);
	//localVertices.push_back(0);

	//// Adding Default Color 
	//localVertices.push_back(1.0f);
	//localVertices.push_back(1.0f);
	//localVertices.push_back(1.0f);

	////Texture?
	//localVertices.push_back(1.0f);
	//localVertices.push_back(0.0f);

	////position
	//localVertices.push_back(1);
	//localVertices.push_back(0);
	//localVertices.push_back(0);

	//// Adding Default Color 
	//localVertices.push_back(1.0f);
	//localVertices.push_back(1.0f);
	//localVertices.push_back(1.0f);

	////Texture?
	//localVertices.push_back(1.0f);
	//localVertices.push_back(0.0f);

	////position
	//localVertices.push_back(2);
	//localVertices.push_back(1);
	//localVertices.push_back(0);

	//// Adding Default Color 
	//localVertices.push_back(1.0f);
	//localVertices.push_back(1.0f);
	//localVertices.push_back(1.0f);

	////Texture?
	//localVertices.push_back(1.0f);
	//localVertices.push_back(0.0f);

	////position
	//localVertices.push_back(2);
	//localVertices.push_back(0);
	//localVertices.push_back(0);

	//// Adding Default Color 
	//localVertices.push_back(1.0f);
	//localVertices.push_back(1.0f);
	//localVertices.push_back(1.0f);

	////Texture?
	//localVertices.push_back(1.0f);
	//localVertices.push_back(0.0f);

	//Indices
	localIndices.push_back(0);
	localIndices.push_back(1);
	localIndices.push_back(2);

	localIndices.push_back(1);
	localIndices.push_back(2);
	localIndices.push_back(3);
}

// Getter: Get Local Vertices
vector<GLfloat>* Rectangle::getVertices() {
	return &localVertices;
}

// Getter: Get Local Indices
vector<GLuint>* Rectangle::getIndices() {
	return &localIndices;
}