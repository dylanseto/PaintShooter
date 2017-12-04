#include "LiquidManager.h"

LiquidManager::LiquidManager() {

	
}

void LiquidManager::createLiquidProjectile() {

	Liquid projectile;

	// LOCAL VERTICES
	for (int i = 0; i < projectile.getParticleCount(); i++) {

		// Particle ID
		localVertices.push_back(projectile.particles[i]->id);

		// Particle Position
		localVertices.push_back(projectile.particles[i]->pos.x);
		localVertices.push_back(projectile.particles[i]->pos.y);
		localVertices.push_back(projectile.particles[i]->pos.z);

		// Particle Paint Color
		localVertices.push_back(paintColor.x);
		localVertices.push_back(paintColor.y);
		localVertices.push_back(paintColor.z);

		// Particle Pressure
		localVertices.push_back(projectile.particles[i]->pressure);

		// Particle Density
		localVertices.push_back(projectile.particles[i]->density);
	}

	// LOCAL NORMALS
	for (int i = 0; i < projectile.getParticleCount(); i++) {
		normalize(projectile.particles[i]->pos);
		localNormals.push_back(projectile.particles[i]->pos.x);
		localNormals.push_back(projectile.particles[i]->pos.y);
		localNormals.push_back(projectile.particles[i]->pos.z);
	}
}


// Setting the Paint Color
void LiquidManager::setPaintColor(glm::vec3 paintColor) {
	this->paintColor = paintColor;
}


// Getter: Get all particle data
vector<GLfloat>* LiquidManager::getVertices() {
	return &localVertices;
}


// Getter: Get all particle normals
vector<GLfloat>* LiquidManager::getNormals() {
	return &localNormals;
}


// Check whether there is data
bool LiquidManager::isEmpty() {
	if (localVertices.empty() && localNormals.empty()) {
		return true;
	}

	return false;
}


// Update Function
void LiquidManager::update(float deltaTime) {

	// Deleted the Liquid that lives past 5 seconds
	if (liquidLifeTime >= 5.0f) {
		localVertices.clear();
		localNormals.clear();
	}

	// Perform Liquid Updates
	else {

		// ====== DO MOVEMENT/POSITION UPDATES ====== //


		// Increase Timer Count
		liquidLifeTime += deltaTime;
	}
}