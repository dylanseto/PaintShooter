
#include "Grid.h"

// Default Constructor
Grid::Grid() {
	
}

// Contructor
Grid::Grid(GLfloat length, int halfGridSize) {
	
	// Generating the Vertices
	for (int horizontal = -halfGridSize; horizontal <= halfGridSize; horizontal++) {
		for (int vertical = -halfGridSize; vertical <= halfGridSize; vertical++) {

			// Adding Position Vertex
			localVertices.push_back((GLfloat)(horizontal * length));
			localVertices.push_back(0.0f);
			localVertices.push_back((GLfloat)(vertical * length));

			// Adding Default Color 
			int randomColorOffset = rand() % 10 + 1;
			localVertices.push_back(GRASS_COLOR.x + ((float)randomColorOffset / 100));
			localVertices.push_back(GRASS_COLOR.y + ((float)randomColorOffset / 100));
			localVertices.push_back(GRASS_COLOR.z + ((float)randomColorOffset / 100));

			// Adding Texture Coordinates
			if (horizontal % 2 == 0 && vertical % 2 == 0) {
				localVertices.push_back(0.0f);
				localVertices.push_back(1.0f);
			}

			else if (horizontal % 2 == 0 && vertical % 2 != 0) {
				localVertices.push_back(0.0f);
				localVertices.push_back(0.0f);
			}

			else if (horizontal % 2 != 0 && vertical % 2 == 0) {
				localVertices.push_back(1.0f);
				localVertices.push_back(1.0f);
			}

			else {
				localVertices.push_back(1.0f);
				localVertices.push_back(0.0f);
			}

			// Adding Grid Texture Opacity
			localVertices.push_back(0.0f);
		}
	}

	// Setting the grid size (Size x Size)
	gridSize = (halfGridSize * 2) + 1;

	// Generating the Indices
	for (int k = 0; k < gridSize - 1; k++) {
		for (int i = 1; i < gridSize; i++) {

			localIndices.push_back((GLuint)(i - 1 + (gridSize * k)));
			localIndices.push_back((GLuint)(i + (gridSize * k)));
			localIndices.push_back((GLuint)(i - 1 + gridSize + (gridSize * k)));
			localIndices.push_back((GLuint)(i + (gridSize * k)));
			localIndices.push_back((GLuint)(i + gridSize + (gridSize * k)));
			localIndices.push_back((GLuint)(i - 1 + gridSize + (gridSize * k)));
		}
	}

	int offset = 9;
	// Generating the Normals
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

// Destructor
Grid::~Grid() {
}

// Getter: Get Local Vertices
vector<GLfloat>* Grid::getVertices() {
	return &localVertices;
}

// Getter: Get Local Indices
vector<GLuint>* Grid::getIndices() {
	return &localIndices;
}

// Getter: Get Local Normals
vector<glm::vec3>* Grid::getNormals() {
	return &localNormals;
}

// Getter: Get Grid Size (Size x Size)
int Grid::getGridSize() {
	return gridSize;
}

// Getter: Get Vertex at given index
glm::vec3 Grid::getVertex(int coordX, int coordY) {

	// Error if coordinates are larger than grid size
	if (coordX > gridSize || coordY > gridSize) {
		cout << "Index out of range (Larger than grid size) " << endl;
		return glm::vec3(0, 0, 0);
	}

	// Return Vec3 containing the values of the vertex
	else {
		int vertexIndex = ((coordX * gridSize) + coordY) * NUM_VERTEX_ATTRIB_OBJ;
		return glm::vec3(localVertices.at(vertexIndex), localVertices.at(vertexIndex + 1), localVertices.at(vertexIndex + 2));
	}
}

// Setter: Change Y value of the found vertex
void Grid::setVertexY(int coordX, int coordY, GLfloat newValue) {

	// Error if coordinates are larger than grid size
	if (coordX > gridSize || coordY > gridSize) {
		cout << "Index out of range (Larger than grid size) " << endl;
	}

	// Change Y Value of given vertex
	else {
		localVertices.at((((coordX * gridSize) + coordY) * NUM_VERTEX_ATTRIB_OBJ) + 1) = newValue;
	}
}



// TEST FUNCTION
void Grid::printGrid() {
	cout << "Vertices " << endl;
	for (int i = 0; i < localVertices.size(); i++) {
		if (i % 3 == 0)
			cout << endl;
		cout << localVertices.at(i) << ", ";
	}

	cout << "Indices" << endl;
	for (int i = 0; i < localIndices.size(); i++) {
		if (i % 3 == 0)
			cout << endl;
		cout << localIndices.at(i) << ", ";
	}
}