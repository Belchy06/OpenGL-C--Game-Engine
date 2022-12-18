#include "Engine.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	GLFWwindow* Window = DisplayManager::CreateDisplay();
	Loader ModelLoader = Loader();
	Renderer ModelRenderer = Renderer();

	Array<float> Vertices = {
		-0.5f, 0.5f, 0.f,
		-0.5f, -0.5f, 0.f,
		0.5f, -0.5f, 0.f,
		0.5f, -0.5f, 0.f,
		0.5f, 0.5f, 0.f,
		-0.5f, 0.5f, 0.f
	};

	RawModel Model = ModelLoader.LoadToVAO(Vertices);

	while (glfwGetKey(Window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(Window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		ModelRenderer.Prepare();
		ModelRenderer.Render(Model);
		// Swap buffers
		glfwSwapBuffers(Window);
		glfwPollEvents();
	}

	ModelLoader.CleanUp();
	return 0;
}