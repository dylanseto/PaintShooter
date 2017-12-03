
#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// GLEW 
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

class Shader {
public:
	// The program ID
	GLuint Program;

	// Constructor and Destructor
	Shader() { }
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//Shader(const GLchar* computePath);
	~Shader();

	// Use the program
	void Use();

protected:
	std::string readFile(std::string fileLocation);
};

#endif