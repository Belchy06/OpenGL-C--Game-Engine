#pragma once

#include "../Models/RawModel.h"
#include "../Models/TexturedModel.h"

#define GLEW_STATIC
#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"
#undef GLEW_STATIC

class Renderer
{
public:
	void Prepare();
	void Render(TexturedModel InModel);
};