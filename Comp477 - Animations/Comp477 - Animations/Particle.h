#pragma once

#include "CommonLibrary.h"

struct Color
{
	unsigned char r, g, b, a;
};

struct Particle
{
	glm::vec3 pos, speed;
	Color color;
	float size, angle, mass;
	float life;
	float cameradistance;

	bool operator<(const Particle& that) const {
		// Sort in reverse order : far particles drawn first.
		return this->cameradistance > that.cameradistance;
	}
};
