#pragma once

#include "CommonLibrary.h"

#include "VertexManager.h"
#include "Rectangle.h"
#include "Grid.h"
#include "Liquid.h"


using namespace std;

class WorldMesh {

	public:

		// Default Constructor
		WorldMesh();

		// Destructor
		~WorldMesh();

		// Getter: Return vertices
		vector<GLfloat>* getVertices() {
			return &vertices;
		};

		// Getter: Return Indices
		vector<GLuint>* getIndices() {
			return &indices;
		};

		// Getter: Return Normals
		vector<glm::vec3>* getNormals() {
			return &normals;
		}

		VertexManager getVertexManager() { 
			return vertexManager; 
		}

		void rotatePerUpdate(GLfloat deltaTime);

	private:
		vector<GLfloat> vertices;
		vector<GLuint> indices;
		vector<glm::vec3> normals;

		VertexManager vertexManager;

		void translateObject(vector<GLfloat>* vertices, glm::vec3 destination);
		void rotateObject(vector<GLfloat>* vertices, float angle);
		void scaleObject(vector<GLfloat>* vertices, float scale);

		// Test Object
		Rectangle rec;
		Grid plane;

};