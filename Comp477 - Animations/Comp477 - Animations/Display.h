#pragma once
#include "CommonLibrary.h"
#include "Shaders\Shader.h"
#include "DensityShader.h"
#include "ForceShader.h"
#include "Camera.h"

class Display {
	public:
		// Create GLFW Display
		Display(std::string windowName, int width, int height);
		~Display();

		GLFWwindow* getWindow();

		bool isClosed();
		void render(float deltaTime);
		void setShader(Shader* shader);
		void setParticleShader(Shader* shader);
		void seParticleDensityShader(DensityShader* shader);
		void seParticleForceShader(ForceShader* shader);
		void setCamera(Camera* cam);
		void setParticleVertices(std::vector<GLfloat>* vertices);
		void setParticleNormals(std::vector<GLfloat>* normals);
		void setVertices(std::vector<GLfloat>* vertices);
		void setIndices(std::vector<GLuint>* indices);
		void setNormals(std::vector<GLfloat>* normals);
		void setLightPos(glm::vec3 lightPos);
		void setLightColor(glm::vec3);
		void setPaintColor(glm::vec3);

		void setNumberOfParticles(int);
		void setParticlePositions(std::vector<glm::vec3>*);
		void setParticleForceData(std::vector<glm::vec4>*);

		void setPressureDensity(int, GLfloat, GLfloat);
		void setForce(glm::vec3 force);

		void clearData();

		std::vector<glm::vec3> actualShotPositions;
		std::vector<glm::vec3> actualColors;

		Camera* getCamera();
		glm::mat4* getViewMatrix();
		glm::mat4* getProjectionMatrix();
		void swapBuffer();

		// void sendStaticDataToBuffer();

	private:
		
		std::string displayName;
		int windowWidth;
		int windowHeight;

		GLFWwindow* window;

		// DYNAMIC: VAO, VBO, EBO
		GLuint VAO[2];
		GLuint VBO[4];
		GLuint EBO;
		
		// Shader
		Shader* ourShader;
		Shader* particleShader;
		DensityShader* particleDensityShader;
		ForceShader* particleForceShader;

		// Vertices and Indices
		std::vector<GLfloat>* localVertices;
		std::vector<GLuint>*  localIndices;
		std::vector<GLfloat>*  localNormals;

		// Light Position
		glm::vec3 localLightPos;

		// Light Color
		glm::vec3 localLightColor;

		// Paint Color
		glm::vec3 localPaintColor;

		// Particle Launch Force
		glm::vec3 launchForce;

		// PARTICLES
		std::vector<GLfloat>* particleVertices;
		std::vector<GLfloat>* particleNormals;
		int numberOfParticles;
		std::vector<glm::vec3>* particlePositions;
		std::vector<glm::vec4>* particleForceData;



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

		GLuint positionTextureBuffer;
		GLuint particlePosBuffer;

		GLuint forcesTextureBuffer;
		GLuint particleForcesBuffer;

		GLuint pressureTBO;
		GLuint forcesTBO;

		static int shot;
};