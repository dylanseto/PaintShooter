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
#include "Camera.h"
#include "WorldMesh.h"
#include "Display.h"

#include "Liquid.h"

using namespace std;

// ========== Function Prototypes ========== //

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void do_movement(GLfloat deltaTime);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


// ========================= Shader File Paths ========================= // 

const GLchar * VERTEX_SHADER_PATH   = "./Shaders/vertex.shader";
const GLchar * FRAGMENT_SHADER_PATH = "./Shaders/fragment.shader";

const GLchar * PARTICLE_VERTEX_SHADER_PATH   = "./Shaders/particle_vertex.shader";
const GLchar * PARTICLE_FRAGMENT_SHADER_PATH = "./Shaders/particle_fragment.shader";
const GLchar * PARTICLE_DENSITY_PRESSURE_SHADER_PATH = "./Shaders/particle_densityPressure.shader";
const GLchar * PARTICLE_FORCES_SHADER_PATH = "./Shaders/particle_densityPressure.shader";



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


const  float fpsLimit = 1.0f / 60.0f;

// Variables to calculate time between frames/update
GLfloat currentTime     = 0.0f;
GLfloat deltaTime       = 0.0f;	// Time between current frame and last frame
GLfloat lastTime        = 0.0f;  	// Time of last frame
GLfloat updateDeltaTime = 0.0f;
GLfloat timer = lastTime;

GLfloat leftMouseHoldTime = 0.0f;
bool leftMouseHold = false;

int frames = 0;
int updates = 0;

// ========== Main Method ========== //
int main() {

	Display animationWindow("Comp 477 - Computer Animations", 1280, 800);
	animationWindow.setCamera(&camera);

	// ========== Creating Our Shapes ========== //
	WorldMesh world;
	vector<GLfloat>*  vertices = world.getVertices();
	vector<GLuint>*    indices = world.getIndices();

	animationWindow.setVertices(vertices);
	animationWindow.setIndices(indices);

	printf("OpenGL version is (%s)\n", glGetString(GL_VERSION));

	// ========== Creating our shaders ========== //
	Shader ourShader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	Shader particleShader(PARTICLE_VERTEX_SHADER_PATH, PARTICLE_FRAGMENT_SHADER_PATH);
	Shader particleDensityShader(PARTICLE_DENSITY_PRESSURE_SHADER_PATH);
	animationWindow.setShader(&ourShader);
	animationWindow.setParticleShader(&particleShader);
	animationWindow.seParticleDensityShader(&particleDensityShader);


	// ---------- CREATING OUR LIQUID ---------- //
	Liquid liq;
	vertices = liq.getVertices();
	animationWindow.setParticleVertices(vertices);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	// =============== SEND STATIC DATA TO GPU =============== 
	// world.rotatePerUpdate(updateDeltaTime);
	// animationWindow.sendStaticDataToBuffer();


	// =============== Game Loop ================= //
	while (!animationWindow.isClosed()) {

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

		/*
		*	UPDATE OUR DYNAMIC OBJECT HERE BASED ON TIME (60 FPS FRAME LOCK)
		*		- Pass in the deltaTime above to calculate new position
		*		- Send new positions to be displayed
		*/
		//std::thread liquidUpdateThread(&Liquid::updateLiquid, liq);

		//liquidUpdateThread.join();
		//liq.updateLiquid();

		//animationWindow.setParticleVertices(vertices);

		while (updateDeltaTime >= 1.0) {

			// world.rotatePerUpdate(updateDeltaTime);

			updates++;
			updateDeltaTime--;
		}	


		// Call Window to Render Image 
		animationWindow.render();
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
		leftMouseHoldTime = 0; // reset Time
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

