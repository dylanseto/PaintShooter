
#include "WorldMesh.h"
#include "Grid.h"
#include "Rectangle.h"


// ==================== Constructor ==================== //
WorldMesh::WorldMesh() : vertexManager(&vertices, &indices) {

	/*
		=========================================================================== 
									Creating Meshes
			You can use this entire section to create the objects to be drawn
		=========================================================================== 
	*/


	// ======= Creating the Grid ======= //
	Grid plane(UNIT, GRID_SIZE);
	Rectangle rec(3,1,2);

	// Rotate, Translate, Scale (Always Rotate First!)
	rotateObject(rec.getVertices(), 45);
	translateObject(rec.getVertices(), glm::vec3(5.0f, 0.0f, 0.0f));
	scaleObject(rec.getVertices(), 2);

	// plane.printGrid();

	// Sending the terrain to the Vertex Manager
	vertexManager.updateMeshes(plane.getVertices(), plane.getIndices());
	vertexManager.updateMeshes(rec.getVertices(), rec.getIndices());


}

	
// Destructor
WorldMesh::~WorldMesh() { }


// Object Scale Function 
void WorldMesh::scaleObject(vector<GLfloat>* vertices, float scale) {

	for (int i = 0; i < vertices->size(); i += NUM_VERTEX_ATTRIB_OBJ) {
		vertices->at(i) *= scale;
		vertices->at(i + 1) *= scale;
		vertices->at(i + 2) *= scale;
	}
}


// Object Translation Function
void WorldMesh::translateObject(vector<GLfloat>* vertices, glm::vec3 destination) {

	for (int i = 0; i < vertices->size(); i += NUM_VERTEX_ATTRIB_OBJ) {
		vertices->at(i) += destination.x;
		vertices->at(i + 1) += destination.y;
		vertices->at(i + 2) += destination.z;
	}
}


// Object Rotation Function Along the Y-Axis
void WorldMesh::rotateObject(vector<GLfloat>* vertices, float angle) {
	
	for (int i = 0; i < vertices->size(); i += NUM_VERTEX_ATTRIB_OBJ) {

		// Instantiating Point and Rotation Matrix
		glm::vec4 point(vertices->at(i), vertices->at(i + 1), vertices->at(i + 2), 1.0f);
		glm::mat4 rotationMatrix;
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

		// Multiplying Point by Rotation Matrix
		point = rotationMatrix * point;
		
		// Set new vertex position
		vertices->at(i) = point.x;
		vertices->at(i + 1) = point.y;
		vertices->at(i + 2) = point.z;
	}
}

