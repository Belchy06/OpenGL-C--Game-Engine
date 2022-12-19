#include "Engine.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Engine GameEngine = Engine();
	return GameEngine.EngineLoop();
}

int Engine::EngineLoop()
{
	GLFWwindow* Window = DisplayManager::CreateDisplay();
	Loader ModelLoader = Loader();
	Renderer ModelRenderer = Renderer();
	StaticShader Shader = StaticShader();

	Array<float> Vertices = {
		-0.5f, 0.5f, 0.f,
		-0.5f, -0.5f, 0.f,
		0.5f, -0.5f, 0.f,
		0.5f, 0.5f, 0.f
	};

	Array<int> Indices = {
		0, 1, 3,
		3, 1, 2
	};

	Array<float> TextureCoords = {
		0, 0,
		0, 1,
		1, 1,
		1, 0
	};

	RawModel Model = ModelLoader.LoadToVAO(Vertices, TextureCoords, Indices);
	ModelTexture Texture = ModelTexture(ModelLoader.LoadTexture("./res/image.png"));
	TexturedModel TextureModel = TexturedModel(Model, Texture);

	while (glfwGetKey(Window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(Window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		ModelRenderer.Prepare();
		Shader.Start();
		ModelRenderer.Render(TextureModel);
		Shader.Stop();
		// Swap buffers
		glfwSwapBuffers(Window);
		glfwPollEvents();
	}

	Shader.CleanUp();
	ModelLoader.CleanUp();
	return 0;
}
