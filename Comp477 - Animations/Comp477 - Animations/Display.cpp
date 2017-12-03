
#include "Display.h"

// ========== Create Windows with set parameters ========== // 
Display::Display(std::string name, int width, int height) {

	// Setting class variables
	displayName = name;
	windowWidth  = width;
	windowHeight = height;

	// Initialize Window Components
	initWindow();
	initGLBuffers();
	// initDynamicGLBuffers();
	loadTextures("Textures/gridTexture.png");
	actualShotPositions = std::vector<glm::vec3>(NUM_SHOTS);
	actualColors = std::vector<glm::vec3>(NUM_SHOTS);
}

// ========== Displpay Destructor ========== // 
Display::~Display() {
	// Frees up the buffers when done 
	glDeleteVertexArrays(1, &VAO[0]);
	glDeleteVertexArrays(1, &VAO[1]);

	glDeleteBuffers(1, &VBO[0]);
	glDeleteBuffers(1, &VBO[1]);

	glDeleteBuffers(1, &EBO);

	// Terminate GLFW Display
	glfwTerminate();
}



// ========== Set the Shader ========== // 
void Display::setShader(Shader* shader) {
	this->ourShader = shader;
}


// ========== Set the Particle Shader ========== // 
void Display::setParticleShader(Shader* shader) {
	this->particleShader = shader;
}

// ========== Set the Shader ========== // 
void Display::setCamera(Camera* cam) {
	this->camera = cam;
}

// ========== Update Window on Draw ========== // 
void Display::loadTextures(GLchar* fileLocation) {
	gridTexture = load2DTexture(fileLocation);
}



// ========== Check whether window is closed ========== // 
void Display::initWindow() {

	// Initiates GLFW and defines the settings
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Enable MSAA (Multi-sampling Anti-Aliasing)
	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);

	// Creates Window Object 
	window = glfwCreateWindow(windowWidth, windowHeight, displayName.c_str(), nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW Windows\n";
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Initiates GLEW (Extension Wrangler) 
	glewExperimental = GLU_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW\n";
		glfwTerminate();
	}

	// Creates the Viewport
	glViewport(0, 0, windowWidth, windowHeight);

	// Enable Z-Buffer
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}


// ========== Creating our Static Vertex Buffer Obj, Vertex Array Obj ========== //
void Display::initGLBuffers() {

	// Creating VAO, VBO, EBO
	glGenVertexArrays(2, VAO);
	glGenBuffers(4, VBO);
	glGenBuffers(1, &EBO);
	
	// ------------- Setting up First VBO (Scene Objects) ------------- //

	// Binding VAO, VBO, EBO
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Set the vertex attribute pointers : POSITION (Px, Py, Pz)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, NUM_VERTEX_ATTRIB_OBJ * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Set the vertex attribute pointers : COLOR (R, G, B)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, NUM_VERTEX_ATTRIB_OBJ * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// ------------- Setting up Second VBO (Normals) ------------- //

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

	// Set the vertex attribute pointers : NORMALS
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(2);

	// ------------- Setting up Third VBO (Collisions) ------------- //
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);

	// Set the vertex attribute pointers : POSITION (Px, Py, Pz)
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, NUM_VERTEX_ATTRIB_OBJ * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(3);

	// Set the vertex attribute pointers : COLOR (R, G, B)
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, NUM_VERTEX_ATTRIB_OBJ * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(4);

	// Unbinding VBO and EBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// ------------- Setting up Fourth VBO (Particles) ------------- //

	// Binding VAO, VBO
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);

	// Set the vertex attribute pointers : POSITION (Px, Py, Pz)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, NUM_PARTICLE_VERTEX_ATTRIB_OBJ * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Set the vertex attribute pointers : COLOR (R, G, B)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, NUM_PARTICLE_VERTEX_ATTRIB_OBJ * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// ------------- Setting up Fifth VBO (Particle Normals) ------------- //

	glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);

	// Set the vertex attribute pointers : NORMALS
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(2);

	// Unbinding VAO
	glBindVertexArray(0);
}


// ========== Update Window on Draw ========== // 
void Display::render() {

	// Rendering Commands
	glClearColor((float)114 / (float)255 * (localLightColor.x + 0.2f), (float)220 / (float)255 * (localLightColor.y + 0.2f), (float)255 / (float)255 * (localLightColor.z + 0.2f), 1.0f);
	// glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ourShader->Use();

	// Using Textures
	glUniform1i(glGetUniformLocation(ourShader->Program, "gridTexture"), 0);

	// Binding Our Textures to Use
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gridTexture);

	// Projection, View, Model 
	projection = glm::perspective(camera->Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
	view = camera->GetViewMatrix(); // Using camera view
	pvm = (projection) * (view);

	GLint lightPosLoc = glGetUniformLocation(ourShader->Program, "lightPos");
	glUniform3f(lightPosLoc, localLightPos.x, localLightPos.y, localLightPos.z);

	GLint lightColorLoc = glGetUniformLocation(ourShader->Program, "lightColor");
	glUniform3f(lightColorLoc, localLightColor.x, localLightColor.y, localLightColor.z);

	GLint collisionColors[NUM_SHOTS];

	// Get Uniform Colors for Collision
	for (int i = 0; i < NUM_SHOTS; i++) {
		std::string name = "paintColors[" + std::to_string(i) + "]";
		collisionColors[i] = glGetUniformLocation(ourShader->Program, name.c_str());
		glUniform3f(collisionColors[i], actualColors[i].x, actualColors[i].y, actualColors[i].z);
	}

	//GLint paintColorLoc = glGetUniformLocation(ourShader->Program, "paintColor");
	//glUniform3f(paintColorLoc, localPaintColor.x, localPaintColor.y, localPaintColor.z);

	glm::vec3 collisionPosition = glm::vec3(10.0f, 0.0f, 10.0f);
	//static bool increasingPosition = true;

	// Max of 10 shots
	GLint collisionPositions[NUM_SHOTS];

	// Get Uniform Locations for Collision
	for (int i = 0; i < NUM_SHOTS; i++) {
		std::string name = "shotPositions[" + std::to_string(i) + "]";
		collisionPositions[i] = glGetUniformLocation(ourShader->Program, name.c_str());
		glUniform3f(collisionPositions[i], actualShotPositions[i].x, 0.0f, actualShotPositions[i].z);
	}

	//GLint shootPositionLoc = glGetUniformLocation(ourShader->Program, "shootPosition");
	//glUniform3f(shootPositionLoc, collisionPosition.x, collisionPosition.y, collisionPosition.z);

	//if (increasingPosition) {
	//	collisionPosition.x++;
	//	collisionPosition.z++;
	//}

	//else {
	//	collisionPosition.x--;
	//	collisionPosition.z--;
	//}

	//if (collisionPosition.x >= 10.0f) {
	//	increasingPosition = !increasingPosition;
	//}
	//else if (collisionPosition.x <= 0.0f) {
	//	increasingPosition = !increasingPosition;
	//}

	GLint viewPosLoc = glGetUniformLocation(ourShader->Program, "viewPos");
	glUniform3f(viewPosLoc, camera->Position.x, camera->Position.y, camera->Position.z);

	static float glowAmount = 0.0f;
	static bool glowIsIncreasing = true;

	GLint emissiveLoc = glGetUniformLocation(ourShader->Program, "emissive");
	glUniform3f(emissiveLoc, glowAmount, 0.0f, 0.0f);

	if (glowIsIncreasing) {
		glowAmount += 0.01f;
	}
	else {
		glowAmount -= 0.01f;
	}

	if (glowAmount >= 0.3f) {
		glowIsIncreasing = !glowIsIncreasing;
	}
	else if (glowAmount <= 0.0f) {
		glowIsIncreasing = !glowIsIncreasing;
	}

	GLint pvmLoc = glGetUniformLocation(ourShader->Program, "pvm");
	glUniformMatrix4fv(pvmLoc, 1, GL_FALSE, glm::value_ptr(pvm));

	// ------------- Drawing Scene Objects ------------- //

	static bool isPrinted = false;
	if (!isPrinted) {
		isPrinted = true;

		for (int i = 0; i < localNormals->size(); i++) {
			std::cout << (*localNormals)[i] <<  " ";
		}
	}

	// Sending Data to the Buffers
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, localVertices->size() * sizeof(GLfloat), &localVertices->front(), GL_DYNAMIC_DRAW);	// Copy our vertices to the buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, localIndices->size() * sizeof(GLuint), &localIndices->front(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, localNormals->size() * sizeof(GLfloat), &localNormals->front(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, localColVertices->size() * sizeof(GLfloat), &localColVertices->front(), GL_DYNAMIC_DRAW);

	// Drawing our Objects
	glDrawElements(GL_TRIANGLES, localIndices->size() * 2, GL_UNSIGNED_INT, 0);


	// ------------- Drawing Particles ------------- //

	// Use Particle Shader to Render Particles (Different Vertex/Fragment Shader)
	particleShader->Use();

	GLint lightPosLoc1 = glGetUniformLocation(particleShader->Program, "lightPos");
	glUniform3f(lightPosLoc1, localLightPos.x, localLightPos.y, localLightPos.z);

	GLint lightColorLoc1 = glGetUniformLocation(particleShader->Program, "lightColor");
	glUniform3f(lightColorLoc1, localLightColor.x, localLightColor.y, localLightColor.z);

	GLint paintColorLoc1 = glGetUniformLocation(particleShader->Program, "paintColor");
	glUniform3f(paintColorLoc1, localPaintColor.x, localPaintColor.y, localPaintColor.z);

	GLint emissiveLoc1 = glGetUniformLocation(particleShader->Program, "emissive");
	glUniform3f(emissiveLoc1, glowAmount, 0.0f, 0.0f);

	GLint viewPosLoc1 = glGetUniformLocation(particleShader->Program, "viewPos");
	glUniform3f(viewPosLoc1, camera->Position.x, camera->Position.y, camera->Position.z);

	pvmLoc = glGetUniformLocation(particleShader->Program, "pvm");
	glUniformMatrix4fv(pvmLoc, 1, GL_FALSE, glm::value_ptr(pvm));

	// Sending Particle Data to the Buffers  
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, particleVertices->size() * sizeof(GLfloat), &particleVertices->front(), GL_DYNAMIC_DRAW);	// Copy our vertices to the buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
	glBufferData(GL_ARRAY_BUFFER, particleNormals->size() * sizeof(GLfloat), &particleNormals->front(), GL_DYNAMIC_DRAW);

	// Drawing our Particles 
	glDrawArrays(GL_POINTS, 0, this->particleVertices->size());

	// Unbinding VAO
	glBindVertexArray(0);

	// Swap the buffers
	glfwSwapBuffers(window);
}


// ========== Send Static Data to Buffers ========== 
//void Display::sendStaticDataToBuffer() {
//	glBindVertexArray(staticVAO);
//	glBufferData(GL_ARRAY_BUFFER, localVertices->size() * sizeof(GLfloat), &localVertices->front(), GL_DYNAMIC_DRAW);	// Copy our vertices to the buffer
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, staticEBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, localIndices->size() * sizeof(GLuint), &localIndices->front(), GL_DYNAMIC_DRAW);
//}




// ========== Check whether window is closed ========== // 
bool Display::isClosed() {
	return glfwWindowShouldClose(window);
}


// ========== Set the Particles' Local Vertices ========== // 
void Display::setParticleVertices(std::vector<GLfloat>* vertices) {
	particleVertices = vertices;
}


// ========== Set the Particles' Local Normals ========== // 
void Display::setParticleNormals(std::vector<GLfloat>* normals) {
	particleNormals = normals;
}


// ========== Set the Local Vertices ========== // 
void Display::setVertices(std::vector<GLfloat>* vertices) {
	localVertices = vertices;
}


// ========== Set the Local Indices ========== // 
void Display::setIndices(std::vector<GLuint>* indices) {
	localIndices = indices;
}

// ========== Set the Local Normals ========== // 
void Display::setNormals(std::vector<GLfloat>* normals) {
	localNormals = normals;
}

// ========== Set the Local Vertices ========== // 
void Display::setColVertices(std::vector<GLfloat>* colVertices) {
	localColVertices = colVertices;
}


// ========== Set the Local Light Position ========== // 
void Display::setLightPos(glm::vec3 lightPos) {
	localLightPos = lightPos;
}

// ========== Set the Local Light Color ========== // 
void Display::setLightColor(glm::vec3 lightColor) {
	localLightColor = lightColor;
}

// ========== Set the Local Light Color ========== // 
void Display::setPaintColor(glm::vec3 paintColor) {
	localPaintColor = paintColor;
}

// Return Pointer to the Window Object
GLFWwindow* Display::getWindow() {
	return window;
}


// Loading 2D Texture Function
GLuint Display::load2DTexture(GLchar* fileLocation) {

	GLuint textureID;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int texWidth, texHeight;
	unsigned char* image = SOIL_load_image(fileLocation, &texWidth, &texHeight, 0, SOIL_LOAD_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);


	return textureID;
}