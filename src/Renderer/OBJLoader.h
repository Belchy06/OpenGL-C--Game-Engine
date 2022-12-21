#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "Loader.h"

#include "../Math/Vector.h"
#include "../Containers/String.h"

#include "../Models/RawModel.h"

class OBJLoader
{
public:
	static RawModel LoadObjModel(const char* InFilePath, Loader InModelLoader);

private:
	static void ProcessVertex(std::vector<std::string> InVertexData, Array<int>& InIndices, Array<Vector2<float>>& InTextures, Array<Vector3<float>>& InNormals, Array<float>& InTexturesArray, Array<float>& InNormalsArray);
};