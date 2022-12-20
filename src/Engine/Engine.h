#pragma once

#include <Windows.h>
#include <tchar.h>

#include "../Textures/ModelTexture.h"
#include "../Entities/Entity.h"
#include "../Models/RawModel.h"
#include "../Models/TexturedModel.h"
#include "../Shaders/StaticShader.h"
#include "../Renderer/DisplayManager.h"
#include "../Renderer/Loader.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/OBJLoader.h"

#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"
#include "../ThirdParty/glfw-3.3.8/include/GLFW/glfw3.h"

class Engine
{
public:
	Engine();
	virtual ~Engine();
	int EngineLoop();

	void HandleKey(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);

	static Engine* GetEngine();

private:
	GLFWwindow* Window;
	Loader* ModelLoader;
	StaticShader* Shader;
	Renderer* ModelRenderer;
	Camera* Cam;

	static Engine* EnginePtr;
};

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
