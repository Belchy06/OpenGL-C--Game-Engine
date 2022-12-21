#pragma once

#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"

class TerrainTexture
{
public:
	TerrainTexture(GLuint InTextureID);
	GLuint GetTextureID() { return TextureID; }

private:
	GLuint TextureID;
};