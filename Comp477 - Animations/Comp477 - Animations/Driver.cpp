/*****
*
*	Johnny Mak (40002140)
*	Helen Tam  (27845537)
*	Dylan Seto (40001991)
*
*	Comp 477 - Computer Animations
*	Project
*
*****/


#include "CommonLibrary.h"
#include "Shaders/Shader.h"
#include "DensityShader.h"
#include "Camera.h"
#include "WorldMesh.h"
#include "Display.h"
#include "Skybox.h"

#include "Liquid.h"

using namespace std;

// ========== Function Prototypes ========== //

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void do_movement(GLfloat deltaTime);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void shoot(Display& animationWindow);
glm::vec3 calculateForce(float mouseHoldTime);


// ========================= Shader File Paths ========================= // 

const GLchar * VERTEX_SHADER_PATH   = "./Shaders/vertex.shader";
const GLchar * FRAGMENT_SHADER_PATH = "./Shaders/fragment.shader";

const GLchar * PARTICLE_VERTEX_SHADER_PATH   = "./Shaders/particle_vertex.shader";
const GLchar * PARTICLE_FRAGMENT_SHADER_PATH = "./Shaders/particle_fragment.shader";
const GLchar * PARTICLE_DENSITYPRESSURE_SHADER_PATH = "./Shaders/particle_densityPressure.shader";
const GLchar * PARTICLE_FORCES_SHADER_PATH = "./Shaders/particle_forces.shader";

const GLchar * SKYBOX_VERTEX_SHADER = "./Shaders/skybox_vertex.shader";
const GLchar * SKYBOX_FRAGMENT_SHADER = "./Shaders/skybox_fragment.shader";



// ========== Constants and Values ========== //


// Camera Object and movement

//Camera camera = Camera(glm::vec3(0.0f, 5.0f, 15.0f));
GLfloat cameraHeight = 3.0f;
Camera camera = Camera(glm::vec3(0.0f, cameraHeight, 15.0f));
GLfloat lastX = 400,
lastY = 300;
bool keys[1024];
bool firstMouse = true;
bool lockCamera = true;

// Skybox Textures IDs
GLuint daySkyboxTextureID;
GLuint nightSkyboxTextureID;
GLuint activeTextureID;


const  float fpsLimit = 1.0f / 60.0f;

// Variables to calculate time between frames/update
GLfloat currentTime     = 0.0f;
GLfloat deltaTime       = 0.0f;	// Time between current frame and last frame
GLfloat lastTime        = 0.0f;  	// Time of last frame
GLfloat updateDeltaTime = 0.0f;
GLfloat timer = lastTime;

// Light Position
glm::vec3 lightPos = glm::vec3(0.0f, 30.0f, 0.0f);

// Light Color
glm::vec3 lightColor;
// Day Color - Faint White
glm::vec3 dayColor = glm::vec3(0.8f, 0.8f, 0.8f);
// Night Color - Blueish
glm::vec3 nightColor = glm::vec3(0.490196f, 0.568627f, 0.670588f);

// Paint Color - Red
glm::vec3 paintColor = glm::vec3(1.0f, 0.0f, 0.0f);

GLfloat leftMouseHoldTime = 0.0f;
bool leftMouseHold = false;

int frames = 0;
int updates = 0;

// ========== Main Method ========== //
int main() {
	srand(time(NULL));

	Display animationWindow("Comp 477 - Computer Animations", 1280, 800);
	animationWindow.setCamera(&camera);

	// ========== Creating Our Shapes ========== //
	WorldMesh world;
	vector<GLfloat>*  vertices = world.getVertices();
	vector<GLuint>*    indices = world.getIndices();
	vector<GLfloat>* normals = world.getNormals();

	animationWindow.setVertices(vertices);
	animationWindow.setIndices(indices);
	animationWindow.setNormals(normals);

	animationWindow.setLightPos(lightPos);

	// Default Lighting
	lightColor = dayColor;

	// ========== Creating our shaders ========== //
	Shader ourShader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	Shader particleShader(PARTICLE_VERTEX_SHADER_PATH, PARTICLE_FRAGMENT_SHADER_PATH);
	DensityShader densityShader(PARTICLE_DENSITYPRESSURE_SHADER_PATH);
	ForceShader forceShader(PARTICLE_FORCES_SHADER_PATH);
	animationWindow.setShader(&ourShader);
	animationWindow.setParticleShader(&particleShader);
	animationWindow.seParticleDensityShader(&densityShader);
	animationWindow.seParticleForceShader(&forceShader);


	// ---------- CREATING OUR LIQUID ---------- //
	Liquid liq;
	vertices = liq.getVertices();
	normals = liq.getNormals();

	animationWindow.setParticleVertices(vertices);
	animationWindow.setParticleNormals(normals);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);




	// --------- Creating the Skybox --------- // 
	Shader skyboxShader(SKYBOX_VERTEX_SHADER, SKYBOX_FRAGMENT_SHADER);
	Skybox skybox(&skyboxShader);

	// Loading Images for Day Skybox
	std::vector<GLchar*> daySkyboxTextures;
	daySkyboxTextures.push_back("./Textures/Day/right.jpg");
	daySkyboxTextures.push_back("./Textures/Day/left.jpg");
	daySkyboxTextures.push_back("./Textures/Day/top.jpg");
	daySkyboxTextures.push_back("./Textures/Day/bottom.jpg");
	daySkyboxTextures.push_back("./Textures/Day/back.jpg");
	daySkyboxTextures.push_back("./Textures/Day/front.jpg");

	// Loading Images for Night Skybox
	std::vector<GLchar*> nightSkyboxTextures;
	nightSkyboxTextures.push_back("./Textures/Night/right.jpg");
	nightSkyboxTextures.push_back("./Textures/Night/left.jpg");
	nightSkyboxTextures.push_back("./Textures/Night/top.jpg");
	nightSkyboxTextures.push_back("./Textures/Night/bottom.jpg");
	nightSkyboxTextures.push_back("./Textures/Night/back.jpg");
	nightSkyboxTextures.push_back("./Textures/Night/front.jpg");

	// Saving the Texture IDs
	daySkyboxTextureID = skybox.loadCubeMap(daySkyboxTextures);
	nightSkyboxTextureID = skybox.loadCubeMap(nightSkyboxTextures);

	// Setting Active Texture ID
	activeTextureID = daySkyboxTextureID;
	skybox.setTextureID(activeTextureID);

	// =============== SEND STATIC DATA TO GPU =============== 
	// world.rotatePerUpdate(updateDeltaTime);
	// animationWindow.sendStaticDataToBuffer();


	// =============== Game Loop ================= //
	while (!animationWindow.isClosed()) {

		if (skybox.getTextureID() != activeTextureID) {
			skybox.setTextureID(activeTextureID);
		}

		// Check and call events
		glfwPollEvents();
		glfwSetKeyCallback(animationWindow.getWindow(), key_callback);
		glfwSetCursorPosCallback(animationWindow.getWindow(), mouse_callback);
	    glfwSetMouseButtonCallback(animationWindow.getWindow(), mouse_button_callback);


		// Calculating DeltaTime (Time Eslapsed since last update/frame)
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		updateDeltaTime += (currentTime - lastTime) / fpsLimit;
		lastTime = currentTime;


		// Check Keyboard Input
		do_movement(deltaTime);
		liq.updateLiquid();

		/*
		*	UPDATE OUR DYNAMIC OBJECT HERE BASED ON TIME (60 FPS FRAME LOCK)
		*		- Pass in the deltaTime above to calculate new position
		*		- Send new positions to be displayed
		*/

		while (updateDeltaTime >= 1.0) {

			// world.rotatePerUpdate(updateDeltaTime);

			updates++;
			updateDeltaTime--;
		}	

		animationWindow.setLightColor(lightColor);
		animationWindow.setPaintColor(paintColor);

		// Call Window to Render Image 
		animationWindow.render();
		skybox.draw(animationWindow.getCamera(), animationWindow.getViewMatrix(), animationWindow.getProjectionMatrix());
		animationWindow.swapBuffer();

		frames++;

		// Displays output Data every second (Frames per second, Updates per second)
		if (glfwGetTime() - timer > 1.0) {
			timer++;
			//std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
			updates = 0, frames = 0;
		}

		if (leftMouseHold) {
			leftMouseHoldTime += deltaTime;
		}
		else if (leftMouseHoldTime != 0) {
			vec3 force = calculateForce(leftMouseHoldTime);
			std::cout << force.x << " " << force.y << " " << force.z << endl;
			leftMouseHoldTime = 0.0f;
			shoot(animationWindow);
		}
	}

	return 0;
}
// ========== End of Main Method ========== //


// Event handler on key press
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {

	if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_ENTER) && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	// Toggle between Locked and Free camera movement
	else if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		lockCamera = !lockCamera;
	}

	// Toggle between Locked and Free camera movement
	else if (key == GLFW_KEY_K && action == GLFW_PRESS) {
		lightColor = dayColor;
		if (activeTextureID != daySkyboxTextureID) {
			activeTextureID = daySkyboxTextureID;
		}
	}

	// Toggle between Locked and Free camera movement
	else if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		lightColor = nightColor;
		if (activeTextureID != nightSkyboxTextureID) {
			activeTextureID = nightSkyboxTextureID;
		}
	}

	else if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		paintColor = RED_COLOR;
	}

	else if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		paintColor = GREEN_COLOR;
	}

	else if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		paintColor = BLUE_COLOR;
	}

	// Smooth camera transitions
	if (key >= 0 && key < 1024 && key != 88) {
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

//Mouse Button Handler
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		cout << "hi" << endl;
		leftMouseHold = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		cout << "Left Mouse Button Was Held for " << leftMouseHoldTime << " seconds" << endl;
		leftMouseHold = false;
	}
}


// Mouse Movement Handler
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}


// Camera movement controls
void do_movement(GLfloat deltaTime) {
	// Press W: Move Forward
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	// Press S: Move Backward
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	// Press A: Move Left
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	// Press D: Move Right
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);

	// Lock camera back to first person view
	if (lockCamera)
		camera.Position.y = cameraHeight;
	// Enable free camera movement
	else if (!lockCamera) {
		// Press Space: Ascend the Camera 
		if (keys[GLFW_KEY_SPACE])
			camera.ProcessKeyboard(UP, deltaTime);
		// Press Left Control: Descent the Camera 
		if (keys[GLFW_KEY_LEFT_CONTROL])
			camera.ProcessKeyboard(DOWN, deltaTime);
	}

	// Press Left Shift: Speed Up Camera
	if (keys[GLFW_KEY_LEFT_SHIFT])
		camera.setCameraSpeed(camera.getDefaultSpeed() * 2);
	// Press C: Slow Down Camera
	else if (keys[GLFW_KEY_C])
		camera.setCameraSpeed(camera.getDefaultSpeed() / 2);
	// Default Speed
	else
		camera.setCameraSpeed(camera.getDefaultSpeed());
}

void shoot(Display& animationWindow) {
	static int i = 0;
	animationWindow.actualShotPositions[i] = camera.Position;
	animationWindow.actualColors[i] = paintColor;
	i++;

	if (i == NUM_SHOTS) {
		i = 0;
	}
}

glm::vec3 calculateForce(float mouseHoldTime) {
	glm::vec3 force;

	// Put a cap on mouseHoldTime to not shoot into infinity
	if (mouseHoldTime >= 5.0f) {
		mouseHoldTime = 5.0f;
	}

	force = mouseHoldTime * camera.Front;

	return force;
}

