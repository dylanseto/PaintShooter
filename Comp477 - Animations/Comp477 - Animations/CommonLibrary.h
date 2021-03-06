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
const GLuint NUM_VERTEX_ATTRIB_OBJ = 6;
const GLuint NUM_PARTICLE_VERTEX_ATTRIB_OBJ = 12;
const GLuint NUM_SHOTS = 20;

// Liquid Life Time
const float LIQUID_LIFE_TIME = 15.0f;


// ================================== Object Sizes ================================== 

// Grid Unit Size (UNIT x UNIT Squares)
const GLfloat UNIT = 1.0f;

// Base Grid Size
const int GRID_SIZE = 50;

// Brightness Constant: Change this value if the color are good and you want to 
//                      adjust the brightness of the world alltogether
const int COLOR_BRIGHTNESS = 10;

// Cube Color RGB
const int CUBE_COLOR_R = 255;
const int CUBE_COLOR_G = 0;
const int CUBE_COLOR_B = 255;

// Grass Color RGB
const int GRASS_COLOR_R = 116;
const int GRASS_COLOR_G = 204;
const int GRASS_COLOR_B = 73;

// Red Color RGB
const int RED_COLOR_R = 255;
const int RED_COLOR_G = 0;
const int RED_COLOR_B = 0;

// Green Color RGB
const int GREEN_COLOR_R = 0;
const int GREEN_COLOR_G = 255;
const int GREEN_COLOR_B = 0;

// Blue Color RGB
const int BLUE_COLOR_R = 0;
const int BLUE_COLOR_G = 0;
const int BLUE_COLOR_B = 255;

// Function to find Float values given color values (0 - 255)
inline float getFloatColor(int colorValue) {

	colorValue += COLOR_BRIGHTNESS;

	if (colorValue >= 0 && colorValue <= 255)
		return ((float)colorValue / (float)255);

	else if (colorValue > 255)
		return 1.0f;

	return 0.0f;
};

// Cube Color
const glm::vec3 CUBE_COLOR(getFloatColor(CUBE_COLOR_R), getFloatColor(CUBE_COLOR_G), getFloatColor(CUBE_COLOR_B));

// Grass Color
const glm::vec3 GRASS_COLOR(getFloatColor(GRASS_COLOR_R), getFloatColor(GRASS_COLOR_G), getFloatColor(GRASS_COLOR_B));


// ======= Blaster Colors ======= //

// Red Color
const glm::vec3 RED_COLOR(getFloatColor(RED_COLOR_R), getFloatColor(RED_COLOR_G), getFloatColor(RED_COLOR_B));

// Green Color
const glm::vec3 GREEN_COLOR(getFloatColor(GREEN_COLOR_R), getFloatColor(GREEN_COLOR_G), getFloatColor(GREEN_COLOR_B));

// Blue Color
const glm::vec3 BLUE_COLOR(getFloatColor(BLUE_COLOR_R), getFloatColor(BLUE_COLOR_G), getFloatColor(BLUE_COLOR_B));


