#pragma once

#include <iostream>
#define GLEW_STATIC
#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"
#undef GLEW_STATIC
#include "../ThirdParty/glfw-3.3.8/include/GLFW/glfw3.h"

class DisplayManager
{
public:
	static GLFWwindow* CreateDisplay();
	static void UpdateDisplay();
	static void CloseDisplay();

private:
	static GLFWwindow* Window;
};