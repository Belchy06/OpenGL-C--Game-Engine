#pragma once

#include "RawModel.h"
#include "../Utility/Array.h"
#include <iostream>

#define GLEW_STATIC
#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"
#undef GLEW_STATIC

class Loader
{
public:
	Loader();

	RawModel LoadToVAO(Array<float> InPositions);
	void CleanUp();

private:
	void CreateVAO(GLuint& OutVaoId);
	void StoreDataInAttributeList(int InAttributeNumber, Array<float> InData, GLuint& OutVboId);
	void UnbindVAO();

	Array<GLuint> VAOs;
	Array<GLuint> VBOs;
};