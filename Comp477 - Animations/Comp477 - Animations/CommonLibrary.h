

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <thread>


// GLEW 
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// SOIL
#include <Soil/SOIL.h>


// Window dimensions (1200x720) 
const GLuint WIDTH = 1280,
			HEIGHT = 720;

// Number of Vertex Attribute Objects
const GLuint NUM_VERTEX_ATTRIB_OBJ = 9;
const GLuint NUM_PARTICLE_VERTEX_ATTRIB_OBJ = 6;

//Mass Of each particle
const float PARTICLE_MASS = 0.02f;

//Right side of ideal gas law, keep constant, to be adjustedd
const float nrt = 5;

const float VISCOSITY_KERNEL = 0.02f;

// ================================== Object Sizes ================================== 

// Grid Unit Size (UNIT x UNIT Squares)
const GLfloat UNIT = 1.0f;

// Base Grid Size
const int GRID_SIZE = 50;

// Particle Neighbour Distance
const float PARTICLE_NEIGHBOUR_DISTANCE = UNIT * 0.5f;

