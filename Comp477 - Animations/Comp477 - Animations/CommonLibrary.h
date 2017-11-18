

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <time.h>


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


// ================================== Object Sizes ================================== 

// Grid Unit Size (UNIT x UNIT Squares)
const GLfloat UNIT = 1.0f;

// Base Grid Size
const int GRID_SIZE = 50;


