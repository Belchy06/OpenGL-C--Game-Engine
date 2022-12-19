#pragma once

#include "../Models/RawModel.h"
#include "../Utility/Array.h"
#include "../Utility/String.h"
#include <iostream>

#include "../ThirdParty/soil/include/SOIL2.h"

#define GLEW_STATIC
#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"
#undef GLEW_STATIC
#include "../ThirdParty/glfw-3.3.8/include/GLFW/glfw3.h"

class Loader
{
public:
	Loader();

	RawModel LoadToVAO(Array<float> InPositions, Array<float> InTextureCoords, Array<int> InIndices);
	GLuint LoadTexture(const char* InTexturePath);
	void CleanUp();

private:
	void CreateVAO(GLuint& OutVaoId);
	void StoreDataInAttributeList(int InAttributeNumber, int InCoordinateSize, Array<float> InData);
	void UnbindVAO();
	void BindIndicesBuffer(Array<int> InIndices);

	Array<GLuint> VAOs;
	Array<GLuint> VBOs;
	Array<GLuint> Textures;

	struct Texture2D
	{
		GLuint TextureID;
		unsigned char* Pixels;
		int Width;
		int Height;
	};
};