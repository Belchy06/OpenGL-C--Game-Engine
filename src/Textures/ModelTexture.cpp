#include "ModelTexture.h"

ModelTexture::ModelTexture(GLuint InTextureID)
	: TextureID(InTextureID)
{
}

GLuint ModelTexture::GetTextureID()
{
	return TextureID;
}
