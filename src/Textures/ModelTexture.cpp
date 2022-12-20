#include "ModelTexture.h"

ModelTexture::ModelTexture(GLuint InTextureID)
	: TextureID(InTextureID)
{
}

GLuint ModelTexture::GetTextureID() const
{
	return TextureID;
}
