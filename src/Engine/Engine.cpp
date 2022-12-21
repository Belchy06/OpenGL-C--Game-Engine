#include "Engine.h"

Engine* Engine::EnginePtr = nullptr;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Engine GameEngine = Engine();

	std::wstringstream SS;
	SS << pCmdLine;
	std::wstring WCmdLine = SS.str();
	OutputDebugString(L"Command Line:");
	OutputDebugString(WCmdLine.c_str());

	OutputDebugString(L"\n");
// clang-format off
	#pragma warning( suppress: 4244 )
	std::string CmdLine(WCmdLine.begin(), WCmdLine.end());
	// clang-format on

	GameEngine.Init(CmdLine);

	return GameEngine.Loop();
}

Engine::Engine()
{
	Window = DisplayManager::CreateDisplay();
	int Flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &Flags);
	if (Flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

	glfwSetKeyCallback(Window, keyCallback);
	ModelLoader = new Loader();
	SceneRenderer = new MasterRenderer();
	Cam = new Camera();
	Cam->SetPosition(Vector3<float>(0, 50, 0));

	EnginePtr = this;

	srand(time(NULL));
}

Engine::~Engine()
{
	EnginePtr = nullptr;
}

int Engine::Init(std::string CommandLine)
{
	using namespace std;

	/* Initialize default values */
	Options["CameraSpeed"] = DEFAULT_CAMERA_SPEED;

	if (CommandLine.size())
	{
		vector<string> CommandLineArgs = String::Split(CommandLine, " ");
		map<string, string> MappedArgs;
		for (string Arg : CommandLineArgs)
		{
			vector<string> KeyValue = String::Split(Arg, "=");
			if (KeyValue.size() == 2)
			{
				MappedArgs[KeyValue[0]] = KeyValue[1];
			}
		}

		if (MappedArgs.find("EngineIniPath") != MappedArgs.end())
		{
			ParseConfig(MappedArgs["EngineIniPath"]);
		}
		else
		{
			ParseConfig(DEFAULT_ENGINE_INI);
		}
	}

	return 0;
}

void Engine::ParseConfig(std::string InConfigPath)
{
	std::ifstream File;
	File.open(InConfigPath);

	if (File.is_open())
	{
		std::string Line;
		while (std::getline(File, Line))
		{
			std::vector<std::string> KeyValue = String::Split(Line, "=");
			if (KeyValue.size() == 2)
			{
				Options[KeyValue[0]] = std::stof(KeyValue[1]);
			}
		}
	}

	File.close();
}

int Engine::Loop()
{
	TexturedModel Tree(OBJLoader::LoadObjModel("./res/tree.obj", *ModelLoader), ModelTexture(ModelLoader->LoadTexture("./res/tree.png")));
	TexturedModel Grass(OBJLoader::LoadObjModel("./res/grass.obj", *ModelLoader), ModelTexture(ModelLoader->LoadTexture("./res/grass.png")));
	Grass.GetModelTexture().SetTransparent(true);
	Grass.GetModelTexture().SetUseFakeLighting(true);
	TexturedModel Fern(OBJLoader::LoadObjModel("./res/fern.obj", *ModelLoader), ModelTexture(ModelLoader->LoadTexture("./res/fern.png")));
	Fern.GetModelTexture().SetTransparent(true);
	Fern.GetModelTexture().SetUseFakeLighting(true);

	Light Sun(Vector3<float>(3000, 2000, 3000), Vector3<float>(1.f));

	Array<Entity> Entities;
	for (int i = 0; i < 200; i++)
	{
		Entities.Add(Entity(Tree, Vector3<float>((float)(rand() / 32767.f) * 800 - 400, 0, (float)(rand() / 32767.f) * -600), Rotator<float>::ZeroRotator(), Vector3<float>(3.f)));
		Entities.Add(Entity(Grass, Vector3<float>((float)(rand() / 32767.f) * 800 - 400, 0, (float)(rand() / 32767.f) * -600), Rotator<float>::ZeroRotator(), Vector3<float>::OneVector()));
		Entities.Add(Entity(Fern, Vector3<float>((float)(rand() / 32767.f) * 800 - 400, 0, (float)(rand() / 32767.f) * -600), Rotator<float>::ZeroRotator(), Vector3<float>(.6f)));
	}

	Array<Terrain> Terrains;
	for (int i = -2; i <= 2; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			Terrains.Add(Terrain(i, j, *ModelLoader, ModelTexture(ModelLoader->LoadTexture("./res/terrain.png"))));
		}
	}

	while (glfwGetKey(Window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(Window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		Terrains.ForEach([this](Terrain InTerrain) {
			SceneRenderer->ProcessTerrain(InTerrain);
		});

		Entities.ForEach([this](Entity InEntity) {
			SceneRenderer->ProcessEntity(InEntity);
		});

		SceneRenderer->Render(Sun, *Cam);
		// Swap buffers
		glfwSwapBuffers(Window);
		glfwPollEvents();
	}

	SceneRenderer->CleanUp();
	ModelLoader->CleanUp();
	return 0;
}

void Engine::HandleKey(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	switch (Key)
	{
		case GLFW_KEY_W:
			Cam->IncreasePosition(Vector3<float>(0.f, 0.f, -Options["CameraSpeed"]));
			break;
		case GLFW_KEY_S:
			Cam->IncreasePosition(Vector3<float>(0.f, 0.f, Options["CameraSpeed"]));
			break;
		case GLFW_KEY_A:
			Cam->IncreasePosition(Vector3<float>(-Options["CameraSpeed"], 0.f, 0.f));
			break;
		case GLFW_KEY_D:
			Cam->IncreasePosition(Vector3<float>(Options["CameraSpeed"], 0.f, 0.f));
			break;
		case GLFW_KEY_LEFT_CONTROL:
			Cam->IncreasePosition(Vector3<float>(0.f, -Options["CameraSpeed"], 0.f));
			break;
		case GLFW_KEY_SPACE:
			Cam->IncreasePosition(Vector3<float>(0.f, Options["CameraSpeed"], 0.f));
			break;
	}
}

Engine* Engine::GetEngine()
{
	return EnginePtr;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Engine* EnginePtr = Engine::GetEngine();
	if (EnginePtr != nullptr)
	{
		EnginePtr->HandleKey(window, key, scancode, action, mods);
	}
}

void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
		return;

	OutputDebugString(L"---------------");
	OutputDebugString(L"\n");
	OutputDebugString(L"Debug message (");
	OutputDebugStringA(std::to_string(id).c_str());
	OutputDebugString(L"): ");
	OutputDebugStringA(message);
	OutputDebugString(L"\n");

	switch (source)
	{
		case GL_DEBUG_SOURCE_API:
			OutputDebugString(L"Source: API");
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			OutputDebugString(L"Source: Window System");
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			OutputDebugString(L"Source: Shader Compiler");
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			OutputDebugString(L"Source: Third Party");
			break;
		case GL_DEBUG_SOURCE_APPLICATION:
			OutputDebugString(L"Source: Application");
			break;
		case GL_DEBUG_SOURCE_OTHER:
			OutputDebugString(L"Source: Other");
			break;
	}
	OutputDebugString(L"\n");

	switch (type)
	{
		case GL_DEBUG_TYPE_ERROR:
			OutputDebugString(L"Type: Error");
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			OutputDebugString(L"Type: Deprecated Behaviour");
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			OutputDebugString(L"Type: Undefined Behaviour");
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			OutputDebugString(L"Type: Portability");
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			OutputDebugString(L"Type: Performance");
			break;
		case GL_DEBUG_TYPE_MARKER:
			OutputDebugString(L"Type: Marker");
			break;
		case GL_DEBUG_TYPE_PUSH_GROUP:
			OutputDebugString(L"Type: Push Group");
			break;
		case GL_DEBUG_TYPE_POP_GROUP:
			OutputDebugString(L"Type: Pop Group");
			break;
		case GL_DEBUG_TYPE_OTHER:
			OutputDebugString(L"Type: Other");
			break;
	}
	OutputDebugString(L"\n");

	switch (severity)
	{
		case GL_DEBUG_SEVERITY_HIGH:
			OutputDebugString(L"Severity: high");
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			OutputDebugString(L"Severity: medium");
			break;
		case GL_DEBUG_SEVERITY_LOW:
			OutputDebugString(L"Severity: low");
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			OutputDebugString(L"Severity: notification");
			break;
	}
	OutputDebugString(L"\n");
	OutputDebugString(L"\n");
}
