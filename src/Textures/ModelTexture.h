#pragma once

#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"

class ModelTexture
{
public:
	ModelTexture(GLuint InTextureID);
	GLuint GetTextureID();

private:
	GLuint TextureID;
};