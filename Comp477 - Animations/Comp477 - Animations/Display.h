#pragma once
#include "CommonLibrary.h"
#include "Shaders\Shader.h"
#include "Camera.h"

class Display {
	public:
		// Create GLFW Display
		Display(std::string windowName, int width, int height);
		~Display();

		GLFWwindow* getWindow();

		bool isClosed();
		void render();
		void setShader(Shader* shader);
		void setCamera(Camera* cam);
		void setVertices(std::vector<GLfloat>* vertices);
		void setIndices(std::vector<GLuint>* indices);

		// void sendStaticDataToBuffer();

	private:
		
		std::string displayName;
		int windowWidth;
		int windowHeight;

		GLFWwindow* window;

		// DYNAMIC: VAO, VBO, EBO
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;

		
		// Shader
		Shader* ourShader;

		// Vertices and Indices
		std::vector<GLfloat>* localVertices;
		std::vector<GLuint>*  localIndices;

		// TextureID
		GLuint gridTexture;
		GLuint load2DTexture(GLchar* fileLocation);

		// Initializes the window 
		void initWindow();
		void initGLBuffers();
		void loadTextures(GLchar* fileLocation);

		// Setting up the Camera
		Camera* camera;

		// GLM Tranformations
		glm::mat4 pvm;
		glm::mat4 view;
		glm::mat4 projection;



};