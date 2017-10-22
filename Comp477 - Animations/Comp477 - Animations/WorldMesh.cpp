
#include "WorldMesh.h"
#include "Grid.h"


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

	// plane.printGrid();

	// Sending the terrain to the Vertex Manager
	vertexManager.updateMeshes(plane.getVertices(), plane.getIndices());


}

	
// Destructor
WorldMesh::~WorldMesh() { }