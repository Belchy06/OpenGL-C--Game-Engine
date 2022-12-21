#pragma once

#include <iostream>

#include <windows.h>
#include <debugapi.h>

#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"
#include "../ThirdParty/glfw-3.3.8/include/GLFW/glfw3.h"

class DisplayManager
{
public:
	static GLFWwindow* CreateDisplay(int InX, int InY);
	static void UpdateDisplay();
	static void CloseDisplay();

	static GLFWwindow* Window;
};