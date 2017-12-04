#include "ForceShader.h"

ForceShader::ForceShader(const GLchar * computePath)
{
	std::string vertexCode = readFile(computePath);

	const GLchar* vShaderCode = vertexCode.c_str();

	GLuint vertex;
	GLint success;
	GLchar infoLog[512];

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	// Print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// Shader Program
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	const GLchar* feedbackVaryings[] = { "ID", "newPos", "newSpeed" };
	glTransformFeedbackVaryings(this->Program, 3, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);
	glLinkProgram(this->Program);

	// Print linking errors if any
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		std::cout << computePath << std::endl;
		system("pause");
	}

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
}
