#pragma once

#include "CommonLibrary.h"

using namespace std;

class VertexManager {

	public: 
		// Constructor
		VertexManager();
		VertexManager(vector<GLfloat>* vertices, vector<GLuint>* indices, vector<GLfloat>* normals);

		// Destructor
		~VertexManager();

		// Class Functions: Helper to Update Vertices, Indices, and Normals (Takes care of call order)
		void VertexManager::updateMeshes(vector<GLfloat>* inputVertices, vector<GLuint>* inputIndices, vector<GLfloat>* inputNormals);


		void clearMesh();

	private: 
		vector<GLfloat>* objectVertices;
		vector<GLuint>* objectIndices;
		vector<GLfloat>* objectNormals;

		void updateVertices(vector<GLfloat>* inputVertices);	// Update Vertices
		void updateIndices(vector<GLuint>* inputIndices);		// Update Indices
		void updateNormals(vector<GLfloat>* inputNormals);		// Update Normals
};