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


using namespace std;

// ========== Function Prototypes ========== //

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void do_movement(GLfloat deltaTime);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);


// ========================= Shader File Paths ========================= // 

const GLchar * VERTEX_SHADER_PATH = "./Shaders/vertex.shader";
const GLchar * FRAGMENT_SHADER_PATH = "./Shaders/fragment.shader";



// ========== Constants and Values ========== //


// Camera Object and movement

Camera camera = Camera(glm::vec3(0.0f, 5.0f, 15.0f));
GLfloat lastX = 400,
lastY = 300;
bool keys[1024];
bool firstMouse = true;

const  float fpsLimit = 1.0f / 60.0f;

// Variables to calculate time between frames/update
GLfloat currentTime     = 0.0f;
GLfloat deltaTime       = 0.0f;	// Time between current frame and last frame
GLfloat lastTime        = 0.0f;  	// Time of last frame
GLfloat updateDeltaTime = 0.0f;
GLfloat timer = lastTime;

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


	// ========== Creating our shaders ========== //
	Shader ourShader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	animationWindow.setShader(&ourShader);


	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	// =============== SEND STATIC DATA TO GPU =============== 
	animationWindow.sendStaticDataToBuffer();


	// =============== Game Loop ================= //
	while (!animationWindow.isClosed()) {

		// Check and call events
		glfwPollEvents();
		glfwSetKeyCallback(animationWindow.window, key_callback);
		glfwSetCursorPosCallback(animationWindow.window, mouse_callback);

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

		while (updateDeltaTime >= 1.0) {
			// scene.update(deltaTime);
			updates++;
			updateDeltaTime--;
		}	


		// Call Window to Render Image 
		animationWindow.render();
		frames++;

		// Displays output Data every second (Frames per second, Updates per second)
		if (glfwGetTime() - timer > 1.0) {
			timer++;
			std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
			updates = 0, frames = 0;
		}

	}

	return 0;
}
// ========== End of Main Method ========== //


// Event handler on key press
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {

	if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_ENTER) && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	// Smooth camera transitions
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
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
	// Press Space: Ascend the Camera 
	if (keys[GLFW_KEY_SPACE])
		camera.ProcessKeyboard(UP, deltaTime);
	// Press Left Control: Descent the Camera 
	if (keys[GLFW_KEY_LEFT_CONTROL])
		camera.ProcessKeyboard(DOWN, deltaTime);

	// Press Left Shift: Speed up Camera
	if (keys[GLFW_KEY_LEFT_SHIFT])
		camera.setCameraSpeed(camera.getDefaultSpeed() * 2);
	// Press C: Slow Down Camera
	else if (keys[GLFW_KEY_C])
		camera.setCameraSpeed(camera.getDefaultSpeed() / 2);
	// Default Speed
	else
		camera.setCameraSpeed(camera.getDefaultSpeed());
}

