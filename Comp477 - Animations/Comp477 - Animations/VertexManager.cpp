
#include "VertexManager.h"


// Default Constructor (Should not be called!)
VertexManager::VertexManager() {
	cout << "Error: Default Consturctor Called!";
}

// Constructor
VertexManager::VertexManager(vector<GLfloat>* vertices, vector<GLuint>* indices, vector<GLfloat>* normals) {
	this->objectVertices = vertices;
	this->objectIndices  = indices;
	this->objectNormals = normals;
}

// Destructor
VertexManager::~VertexManager() {
}

// Updates the Vertices  
void VertexManager::updateVertices(vector<GLfloat>* inputVertices) {

	objectVertices->insert(objectVertices->end(), inputVertices->begin(), inputVertices->end());
}

// Updates the Indices 
void VertexManager::updateIndices(vector<GLuint>* inputIndices) {

	GLuint offset = objectVertices->size() / NUM_VERTEX_ATTRIB_OBJ;

	for (int i = 0; i < inputIndices->size(); i++) {
		objectIndices->push_back(inputIndices->at(i) + offset);
	}
}

// Updates the Normals
void VertexManager::updateNormals(vector<GLfloat>* inputNormals) {

	objectNormals->insert(objectNormals->end(), inputNormals->begin(), inputNormals->end());
}

// Helper Function: Update Vertices and Indices
void VertexManager::updateMeshes(vector<GLfloat>* inputVertices, vector<GLuint>* inputIndices, vector<GLfloat>* inputNormals) {
	updateIndices(inputIndices);
	updateVertices(inputVertices);
	updateNormals(inputNormals);
}

// Clear the mesh Data
void VertexManager::clearMesh() {
	objectVertices->clear();
	objectIndices->clear();
	objectNormals->clear();
}