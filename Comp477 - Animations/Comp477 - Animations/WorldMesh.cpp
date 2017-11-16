
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

	// plane.printGrid();

	// Sending the terrain to the Vertex Manager
	vertexManager.updateMeshes(plane.getVertices(), plane.getIndices());
	vertexManager.updateMeshes(rec.getVertices(), rec.getIndices());


}

	
// Destructor
WorldMesh::~WorldMesh() { }