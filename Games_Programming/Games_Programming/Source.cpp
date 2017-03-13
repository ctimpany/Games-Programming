// Simplified Renderer application for GP course
// Code is similar to the one in lab 1 but all the graphics sections were refactored into the Graphics Class.
// Extra improvements:
// Reduced OpenGL version from 4.5 to 3.3 to allow it to render in older laptops.
// Added Shapes library for rendering cubes, spheres and vectors.
// Added examples of matrix multiplication on Update.
// Added resize screen and keyboard callbacks.
// 
// Suggestions or extra help please do email me S.Padilla@hw.ac.uk
//
// Note: Do not forget to link the libraries correctly and add the GLEW DLL in your debug/release folder.

#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>

#include "graphics.h"
#include "shapes.h"
#include "PhysicsSphere.h"

// FUNCTIONS
void render(double currentTime);
void update(double currentTime);
void startup();
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

// VARIABLES
bool		running = true;

Graphics	myGraphics;		// Runing all the graphics in this object

Sphere		mySphere;
PhysicsSphere phys;

float t = 0.001f;			// Global variable for animation


float			angleX = 0.0f;
float			angleY = 0.0f;
float			disp = -5.0;
float			fovy = 45.0f;
float			posX = 0.0f, posY = -10.0f, posZ = 50.0f;
glm::vec3		cameraPosition = glm::vec3(posX, posY, posZ);
glm::vec3		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
GLfloat			yaw = -90.0f;	// init pointing to inside
GLfloat			pitch = 0.0f;	// start centered



int main()
{
	int errorGraphics = myGraphics.Init();		// Launch window and graphics context
	if (errorGraphics) return 0;				//Close if something went wrong...

	startup();									// Setup all necessary information for startup (aka. load texture, shaders, models, etc).
	
	// Mixed graphics and update functions - declared in main for simplicity.
	glfwSetWindowSizeCallback(myGraphics.window, onResizeCallback);			// Set callback for resize
	glfwSetKeyCallback(myGraphics.window, onKeyCallback);					// Set Callback for keys

	// MAIN LOOP run until the window is closed
	do {										
		double currentTime = glfwGetTime();		// retrieve timelapse
		glfwPollEvents();						// poll callbacks
		update(currentTime);					// update (physics, animation, structures, etc)
		render(currentTime);					// call render function.

		glfwSwapBuffers(myGraphics.window);		// swap buffers (avoid flickering and tearing)

		running &= (glfwGetKey(myGraphics.window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);	// exit if escape key pressed
		running &= (glfwWindowShouldClose(myGraphics.window) != GL_TRUE);
	} while (running);

	myGraphics.endProgram();			// Close and clean everything up...

	cout << "\nPress any key to continue...\n";
	cin.ignore(); cin.get(); // delay closing console to read debugging errors.

	return 0;
}

void startup() {
	
	// Calculate proj_matrix for the first time.
	myGraphics.aspect = (float)myGraphics.windowWidth / (float)myGraphics.windowHeight;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);

	// Load Geometry
	mySphere.Load();
	mySphere.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);	// You can change the shape fill colour, line colour or linewidth


	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(front);


	myGraphics.SetOptimisations();		// Cull and depth testing
}

void update(double currentTime) {
	glm::mat4 viewMatrix = glm::lookAt(cameraPosition,					// eye
		cameraPosition + cameraFront,	// centre
		cameraUp);						// up

	// calculate Sphere movement
	phys.Update();

	glm::mat4 mv_matrix_sphere2 =
		glm::translate(phys.getPosition()) *
		glm::scale(glm::vec3(1.0f, 1.0f, 1.0f)) *
		glm::mat4(1.0f);
	mySphere.mv_matrix =viewMatrix * mv_matrix_sphere2;
	mySphere.proj_matrix = myGraphics.proj_matrix;
}

void render(double currentTime) {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();
	mySphere.Draw();
}

void onResizeCallback(GLFWwindow* window, int w, int h) {	// call everytime the window is resized
	myGraphics.windowWidth = w;
	myGraphics.windowHeight = h;

	myGraphics.aspect = (float)w / (float)h;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);
}

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { // called everytime a key is pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	//if (key == GLFW_KEY_RIGHT) posX += 1.0f;

	//if (key == GLFW_KEY_LEFT) angleY += 0.05f;
}