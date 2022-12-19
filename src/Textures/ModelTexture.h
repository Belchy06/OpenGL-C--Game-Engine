#pragma once

#define GLEW_STATIC
#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"
#undef GLEW_STATIC

class ModelTexture
{
public:
	ModelTexture(GLuint InTextureID);
	GLuint GetTextureID();

private:
	GLuint TextureID;
};