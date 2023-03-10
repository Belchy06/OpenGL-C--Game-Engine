#pragma once

#include <iostream>

#include "../Containers/Array.h"
#include "../Models/RawModel.h"

#include "../ThirdParty/soil/include/SOIL2.h"
#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"
#include "../ThirdParty/glfw-3.3.8/include/GLFW/glfw3.h"

class Loader
{
public:
	Loader();

	RawModel LoadToVAO(Array<float> InPositions, Array<float> InTextureCoords, Array<int> InIndices, Array<float> InNormals);
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
};