#pragma once

#include "CommonLibrary.h"
using namespace std;

struct Color
{
	float r, g, b, a;
};

class Particle
{
public:
	int id;
	glm::vec3 pos, speed;
	float cameradistance;
	float density;
	float pressure;

	Particle()
	{
	}

	bool operator<(const Particle& that) const {
		// Sort in reverse order : far particles drawn first.
		return this->cameradistance > that.cameradistance;
	}
};
