#pragma once

#ifndef ForceSHADER_H
#define ForceSHADER_H

#include "Shaders\Shader.h"


class ForceShader : public Shader {
public:
	ForceShader(const GLchar* computePath);
};

#endif