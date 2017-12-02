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
				// Adding Position
				localVertices.push_back(x * length * UNIT);
				localVertices.push_back(y * height * UNIT);
				localVertices.push_back(z * height * UNIT);

				// Adding Default Color 
				int randomColorOffset = rand() % 10 + 1;

				localVertices.push_back(CUBE_COLOR.x + ((float)randomColorOffset / 100));
				localVertices.push_back(CUBE_COLOR.y + ((float)randomColorOffset / 100));
				localVertices.push_back(CUBE_COLOR.z + ((float)randomColorOffset / 100));

				// Adding Textures
				localVertices.push_back(1.0f);
				localVertices.push_back(1.0f);

				// Adding Texture Opacity
				localVertices.push_back(0.0f);
			}
		}
	}

	// Adding Indices

	// Right side
	localIndices.push_back(0);
	localIndices.push_back(1);
	localIndices.push_back(2);

	localIndices.push_back(3);
	localIndices.push_back(1);
	localIndices.push_back(2);

	// Left Side
	localIndices.push_back(4);
	localIndices.push_back(5);
	localIndices.push_back(6);

	localIndices.push_back(7);
	localIndices.push_back(5);
	localIndices.push_back(6);


	// Top
	localIndices.push_back(0);
	localIndices.push_back(1);
	localIndices.push_back(5);

	localIndices.push_back(0);
	localIndices.push_back(4);
	localIndices.push_back(5);

	// Bottom
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

	// Back
	localIndices.push_back(0);
	localIndices.push_back(2);
	localIndices.push_back(4);

	localIndices.push_back(6);
	localIndices.push_back(2);
	localIndices.push_back(4);

	// Adding Normals
	int offset = 6;
	for (int i = 0; i < localIndices.size(); i += 3) {
		vector1 = glm::vec3(localVertices[localIndices[i + 1] * offset] - localVertices[localIndices[i] * offset],
			localVertices[localIndices[i + 1] * offset + 1] - localVertices[localIndices[i] * offset + 1],
			localVertices[localIndices[i + 1] * offset + 2] - localVertices[localIndices[i] * offset + 2]);
		vector2 = glm::vec3(localVertices[localIndices[i + 2] * offset] - localVertices[localIndices[i] * offset],
			localVertices[localIndices[i + 2] * offset + 1] - localVertices[localIndices[i] * offset + 1],
			localVertices[localIndices[i + 2] * offset + 2] - localVertices[localIndices[i] * offset + 2]);
		vectorProduct = cross(vector1, vector2);
		localNormals.push_back(normalize(vectorProduct));
	}
}

// Getter: Get Local Vertices
vector<GLfloat>* Rectangle::getVertices() {
	return &localVertices;
}

// Getter: Get Local Indices
vector<GLuint>* Rectangle::getIndices() {
	return &localIndices;
}

vector<glm::vec3>* Rectangle::getNormals() {
	return &localNormals;
}