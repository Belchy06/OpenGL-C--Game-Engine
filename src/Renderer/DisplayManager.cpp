#include "DisplayManager.h"

GLFWwindow* DisplayManager::Window;

GLFWwindow* DisplayManager::CreateDisplay()
{
	glewExperimental = GL_TRUE;
	if (!glfwInit())
	{
		OutputDebugString(L"Failed to init glfw!");
		return nullptr;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);			   // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);		   // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	// Open a window and create its OpenGL context
	Window = glfwCreateWindow(1024, 768, "Engine", NULL, NULL);
	if (Window == NULL)
	{
		OutputDebugString(L"Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(Window); // Initialize GLEW

	glewInit();
	GLenum Err = glewInit();
	if (Err != GLEW_OK)
	{
		OutputDebugString(L"glewInit failed!");
		return nullptr;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(Window, GLFW_STICKY_KEYS, GL_TRUE);

	return Window;
}

void DisplayManager::UpdateDisplay()
{
}

void DisplayManager::CloseDisplay()
{
}