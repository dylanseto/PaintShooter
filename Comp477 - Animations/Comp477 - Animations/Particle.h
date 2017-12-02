#pragma once

#include "CommonLibrary.h"
using namespace std;

struct Color
{
	float r, g, b, a;
};

struct Particle
{
	glm::vec3 pos, speed;
	Color color;
	float size, angle, mass;
	float life;
	float cameradistance;
	string hashKey;

	bool operator<(const Particle& that) const {
		// Sort in reverse order : far particles drawn first.
		return this->cameradistance > that.cameradistance;
	}
};
