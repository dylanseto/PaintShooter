#pragma once


#ifndef DENSITYSHADER_H
#define DENSITYSHADER_H

#include "Shaders\Shader.h"


class DensityShader : public Shader {
public:
	DensityShader(const GLchar* computePath);
};

#endif