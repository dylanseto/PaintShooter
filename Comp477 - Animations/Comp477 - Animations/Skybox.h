#pragma once

#include "CommonLibrary.h"
#include "Shaders/Shader.h"

#include "Camera.h"

class Skybox {

public:
	Skybox();
	Skybox(Shader* shader);
	~Skybox();

	GLuint loadCubeMap(std::vector<GLchar*> fileLocation);
	void draw(Camera* cam, glm::mat4* view, glm::mat4* projection);
	void setTextureID(GLuint textureID);
	GLuint getTextureID();

private:
	std::vector<GLfloat>* localVertices;
	Shader* localShader;

	GLuint skyboxVAO, skyboxVBO, textureID;

};