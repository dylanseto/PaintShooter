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
				//position
				localVertices.push_back(x * length * UNIT);
				localVertices.push_back(y * height * UNIT);
				localVertices.push_back(z * height * UNIT);

				//cout << "Index " << i << ":(" << x << "," << y << "," << z << ")" << endl;
				i++;

				// Adding Default Color 
				localVertices.push_back(1.0f);
				localVertices.push_back(0.0f);
				localVertices.push_back(1.0f);


				// Adding Textures
				localVertices.push_back(1.0f);
				localVertices.push_back(1.0f);

				// Adding Texture Opacity
				localVertices.push_back(0.0f);

			}
		}
	}

	//Indices

	//Right side
	localIndices.push_back(0);
	localIndices.push_back(1);
	localIndices.push_back(2);

	localIndices.push_back(3);
	localIndices.push_back(1);
	localIndices.push_back(2);

	//Left Side
	localIndices.push_back(4);
	localIndices.push_back(5);
	localIndices.push_back(6);

	localIndices.push_back(7);
	localIndices.push_back(5);
	localIndices.push_back(6);


	//Top
	localIndices.push_back(0);
	localIndices.push_back(1);
	localIndices.push_back(5);

	localIndices.push_back(0);
	localIndices.push_back(4);
	localIndices.push_back(5);

	//Bottom
	localIndices.push_back(3);
	localIndices.push_back(6);
	localIndices.push_back(2);

	localIndices.push_back(3);
	localIndices.push_back(6);
	localIndices.push_back(7);


	//Front
	localIndices.push_back(1);
	localIndices.push_back(3);
	localIndices.push_back(5);

	localIndices.push_back(7);
	localIndices.push_back(3);
	localIndices.push_back(5);

	//Back
	localIndices.push_back(0);
	localIndices.push_back(2);
	localIndices.push_back(4);

	localIndices.push_back(6);
	localIndices.push_back(2);
	localIndices.push_back(4);

}

// Getter: Get Local Vertices
vector<GLfloat>* Rectangle::getVertices() {
	return &localVertices;
}

// Getter: Get Local Indices
vector<GLuint>* Rectangle::getIndices() {
	return &localIndices;
}