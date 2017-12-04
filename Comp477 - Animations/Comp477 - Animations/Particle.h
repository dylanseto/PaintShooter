#pragma once

#include "CommonLibrary.h"
using namespace std;

struct Color
{
	float r, g, b, a;
};

struct Particle
{
	glm::vec3 pos, speed, acceleration;
	Color color;
	int id;
	float size, angle, mass;
	float life;
	float cameradistance;
	float density;
	float pressure;
	//string hashKey = "";
	bool moved = false;

	bool operator<(const Particle& that) const {
		// Sort in reverse order : far particles drawn first.
		return this->cameradistance > that.cameradistance;
	}
};
