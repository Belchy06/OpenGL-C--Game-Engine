#include "Engine.h"

Engine* Engine::EnginePtr = nullptr;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Engine GameEngine = Engine();
	return GameEngine.EngineLoop();
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
	Shader = new StaticShader();
	ModelRenderer = new Renderer(*Shader);
	Cam = new Camera();

	EnginePtr = this;
}

Engine::~Engine()
{
	EnginePtr = nullptr;
}

int Engine::EngineLoop()
{
	RawModel Model = OBJLoader::LoadObjModel("./res/dragon.obj", *ModelLoader);
	ModelTexture Texture(ModelLoader->LoadTexture("./res/white.png"));
	TexturedModel TextureModel(Model, Texture);

	Entity Ent(TextureModel, Vector3<float>(0, 0, -25.f), Rotator<float>(0.f), Vector3<float>(1.f));
	Light Lit(Vector3<float>(0, 0, -20.f), Vector3<float>(1.f));
	while (glfwGetKey(Window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(Window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		Ent.IncreaseRotation(Vector3<float>(0.f, .01f, 0.f));
		ModelRenderer->Prepare();
		Shader->Start();
		Shader->LoadLight(Lit);
		ModelRenderer->Render(Ent, *Cam);
		Shader->Stop();
		// Swap buffers
		glfwSwapBuffers(Window);
		glfwPollEvents();
	}

	Shader->CleanUp();
	ModelLoader->CleanUp();
	return 0;
}

void Engine::HandleKey(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	switch (Key)
	{
		case GLFW_KEY_W:
			Cam->IncreasePosition(Vector3<float>(0.f, 0.f, 0.02f));
			break;
		case GLFW_KEY_S:
			Cam->IncreasePosition(Vector3<float>(0.f, 0.f, -0.02f));
			break;
		case GLFW_KEY_A:
			Cam->IncreasePosition(Vector3<float>(0.02f, 0.f, 0.f));
			break;
		case GLFW_KEY_D:
			Cam->IncreasePosition(Vector3<float>(-0.02f, 0.f, 0.f));
			break;
		case GLFW_KEY_LEFT_CONTROL:
			Cam->IncreasePosition(Vector3<float>(0.f, -0.02f, 0.f));
			break;
		case GLFW_KEY_SPACE:
			Cam->IncreasePosition(Vector3<float>(0.f, 0.02f, 0.f));
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
