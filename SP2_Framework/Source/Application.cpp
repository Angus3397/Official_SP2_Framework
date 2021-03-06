/******************************************************************************/
/*!
\file	Application.cpp
\author Team NoticeMeSenpai
\brief
Initialise opengl function
*/
/******************************************************************************/
#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "Scene_SuperMarket.h"
#include "2D_PhysicAndCollision.h"
#include "3D_PhysicAndCollision.h"

GLFWwindow* m_window;
const unsigned char FPS = 200; // FPS of this game
const unsigned int frameTime = 1000/FPS; // time for each frame

/******************************************************************************/
/*!
\brief
Define an error callback

\param error
\param description
*/
/******************************************************************************/
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

/******************************************************************************/
/*!
\brief
Define the key input callback

\param window - current window
\param w - width of the window
\param h - height of the window
*/
/******************************************************************************/
void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0,0,w,h);
}

/******************************************************************************/
/*!
\brief
Define the key input callback

\param window - current window
\param key - keyboard
\param scancode
\param action
\param mods
*/
/******************************************************************************/
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

/******************************************************************************/
/*!
\brief
Check if the keyboard key is pressed

\param key - keyboard key
*/
/******************************************************************************/
bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}



/******************************************************************************/
/*!
\brief
Default constructor - initialise variables 
*/
/******************************************************************************/
Application::Application()
{
    windowMidX = 1000  / 2.0f;
	windowMidY = 800 / 2.0f;
}

/******************************************************************************/
/*!
\brief
Default destructor
*/
/******************************************************************************/
Application::~Application()
{

}

/******************************************************************************/
/*!
\brief
Initialise OPENGL or variables
*/
/******************************************************************************/
void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 
    
	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(1000, 800, "Computer Graphics", NULL, NULL);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	glfwSetKeyCallback(m_window, key_callback);

	glfwSetWindowSizeCallback(m_window, resize_callback);
	glewExperimental = true; // Needed for core profile

	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
    
    //glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetCursorPos(m_window, windowMidX, windowMidY);
}

/******************************************************************************/
/*!
\brief
run the code
*/
/******************************************************************************/
void Application::Run()
{
	//Main Loop
	Scene *scene = new threeD_scene();  //Linked list?
	scene->Init();
	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
		scene->Update(m_timer.getElapsedTime());
		scene->Render();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
	scene->Exit();
	delete scene;
}

/******************************************************************************/
/*!
\brief
Close window and terminate GLFW
*/
/******************************************************************************/
void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
