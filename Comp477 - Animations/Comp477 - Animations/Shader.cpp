
#include "Shaders/Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {

	std::string vertexCode   = readFile(vertexPath);
	std::string fragmentCode = readFile(fragmentPath);

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
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

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	// Print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// Shader Program
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);

	// Print linking errors if any
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

// Destructor
Shader::~Shader() {
	glDeleteProgram(this->Program);
}

// Use Shader Function
void Shader::Use() { 
	glUseProgram(this->Program); 
}

// Read File
std::string Shader::readFile(std::string fileLocation) {

	std::string fileContent;
	std::ifstream file;

	// ensures ifstream object can throw exceptions:
	file.exceptions(std::ifstream::badbit);

	try  {
		// Open file
		file.open(fileLocation);

		std::stringstream stream;
		stream << file.rdbuf();

		file.close();

		// Convert stream into string
		fileContent = stream.str();
	}

	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ:\"" << fileLocation << "\"" << std::endl;
	}

	return fileContent;
}