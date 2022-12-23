#pragma once

#include <time.h>
#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <chrono>
#include <ctime>
#include <memory>
#include <set>

#include "Defaults.h"
#include "../Textures/ModelTexture.h"
#include "../Entities/Entity.h"
#include "../Entities/Light.h"
#include "../Entities/Player.h"
#include "../Terrain/Terrain.h"
#include "../Models/RawModel.h"
#include "../Models/TexturedModel.h"
#include "../Shaders/StaticShader.h"
#include "../Renderer/DisplayManager.h"
#include "../Renderer/Loader.h"
#include "../Renderer/MasterRenderer.h"
#include "../Renderer/OBJLoader.h"
#include "../Delegates/Delegate.h"

#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"
#include "../ThirdParty/glfw-3.3.8/include/GLFW/glfw3.h"

#define DEFAULT_ENGINE_INI "./config/Engine.ini"

class Engine
{
public:
	Engine();
	virtual ~Engine();

	int Init(std::string CommandLine);
	int Loop();
	void HandleKey(GLFWwindow* InWindow, int InKey, int InScancode, int InAction, int InMods);
	void HandleMousePos(GLFWwindow* InWindow, double InXPos, double InYPos);
	void HandleMouseWheel(GLFWwindow* InWindow, double InXOffset, double InYOffset);

	static Engine* GetEngine();
	static std::map<std::string, float> OPTIONS;
	static std::set<Object*> Objects;

	static MulticastDelegate<Vector2<double>, Vector2<double>> MouseMove;
	static MulticastDelegate<double> MouseWheel;
	static MulticastDelegate<int> KeyUp;
	static MulticastDelegate<int> KeyDown;

private:
	void ParseConfig(std::string InConfigPath);

	GLFWwindow* Window;
	Loader* ModelLoader;
	MasterRenderer* SceneRenderer;

	std::map<std::string, std::string> MappedArgs;

	static Engine* EnginePtr;

	std::chrono::system_clock::time_point LastFrameTime;
	std::chrono::duration<float> DeltaTime;
	float TargetFrameDelta;

	Vector2<double> MousePos;
	Vector2<double> MousePosLastTick;
};

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void cursorScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);