
#include "WorldMesh.h"



// ==================== Constructor ==================== //
WorldMesh::WorldMesh() : vertexManager(&vertices, &indices, &normals) {

	/*
		=========================================================================== 
									Creating Meshes
			You can use this entire section to create the objects to be drawn
		=========================================================================== 
	*/


	// ======= Creating the Grid ======= //
	plane = Grid(UNIT, GRID_SIZE);
	// Sending the terrain to the Vertex Manager
	vertexManager.updateMeshes(plane.getVertices(), plane.getIndices(), plane.getNormals());

	int min = 1;
	int max = 5;

	int gridMin = -plane.getGridSize() / (2 / UNIT);
	int gridMax = plane.getGridSize() / (2 / UNIT);

	int numOfWalls = GRID_SIZE / 3;

	// ======= Creating Rectangular Walls ======= //
	for (int i = 0; i < numOfWalls; i++) {
		int randomX = rand() % max + min;
		int randomY = rand() % max + min;
		int randomZ = rand() % max + min;

		//rec = Rectangle(3, 2, 1);
		Rectangle* rec = new Rectangle(randomX, randomY, randomZ);

		float randomTransX = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX + 1)) * (gridMax / 2.2 - gridMin / 2.2) + gridMin / 2.2;
		float randomTransZ = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX + 1)) * (gridMax / 2.2 - gridMin / 2.2) + gridMin / 2.2;

		// Rotate, Translate, Scale (Always Rotate First!)
		int randomDegree = rand() % 45 + 1;
		//rotateObject(rec.getVertices(), 45);
		//rotateObject(rec.getVertices(), randomDegree);

		//translateObject(rec.getVertices(), glm::vec3(5.0f, 0.0f, 0.0f));
		translateObject(rec->getVertices(), glm::vec3(randomTransX, 0.0f, randomTransZ));

		float randomScale = (float)(rand() % 2 + 1) + 0.1 * (float)(rand() % 3 + 1);
		//scaleObject(rec.getVertices(), 2);
		scaleObject(rec->getVertices(), randomScale);

		// plane.printGrid();

		// Sending the Rectangle objects to the Vertex Manager
		vertexManager.updateMeshes(rec->getVertices(), rec->getIndices(), rec->getNormals());
		rectangles.push_back(rec);
		
	}
}

	
// Destructor
WorldMesh::~WorldMesh() { }


// Test Function: Rotate object per second
void WorldMesh::rotatePerUpdate(GLfloat deltaTime) {
	//rotateObject(rec.getVertices(), 1 * deltaTime);

	vertexManager.clearMesh();
	// vertexManager.updateMeshes(plane.getVertices(), plane.getIndices());
	//vertexManager.updateMeshes(rec.getVertices(), rec.getIndices(), rec.getNormals());
}

WorldMesh* WorldMesh::instance;
WorldMesh * WorldMesh::getInstance()
{
	if (instance == nullptr) instance = new WorldMesh();

	return instance;
}


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

