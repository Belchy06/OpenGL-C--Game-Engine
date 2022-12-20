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
	Array<float> Vertices = {
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,

		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,

		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,

		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,

		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, 0.5f,

		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f

	};

	Array<float> TextureCoords = {

		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0

	};

	Array<int> Indices = {
		0, 1, 3,
		3, 1, 2,
		4, 5, 7,
		7, 5, 6,
		8, 9, 11,
		11, 9, 10,
		12, 13, 15,
		15, 13, 14,
		16, 17, 19,
		19, 17, 18,
		20, 21, 23,
		23, 21, 22

	};

	RawModel Model = ModelLoader->LoadToVAO(Vertices, TextureCoords, Indices);
	ModelTexture Texture(ModelLoader->LoadTexture("./res/image.png"));
	TexturedModel TextureModel(Model, Texture);

	Entity Ent(TextureModel, Vector3<float>(0, 0, -5.f), Rotator<float>(0.f), Vector3<float>(1.f));

	while (glfwGetKey(Window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(Window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		Ent.IncreaseRotation(Vector3<float>(.01f, .01f, 0.f));
		ModelRenderer->Prepare();
		Shader->Start();
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
		case GLFW_KEY_A:
			Cam->IncreasePosition(Vector3<float>(0.02f, 0.f, 0.f));
			break;
		case GLFW_KEY_S:
			Cam->IncreasePosition(Vector3<float>(0.f, 0.f, -0.02f));
			break;
		case GLFW_KEY_D:
			Cam->IncreasePosition(Vector3<float>(-0.02f, 0.f, 0.f));
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
