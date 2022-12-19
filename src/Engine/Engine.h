#pragma once

#include <Windows.h>
#include <tchar.h>
#include "../Renderer/DisplayManager.h"
#include "../Renderer/Loader.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/RawModel.h"
#include "../Renderer/StaticShader.h"

#define GLEW_STATIC
#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"
#undef GLEW_STATIC
#include "../ThirdParty/glfw-3.3.8/include/GLFW/glfw3.h"

class Engine
{
public:
	int EngineLoop();
};
