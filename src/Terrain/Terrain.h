#pragma once

#include "../Containers/Array.h"
#include "../Renderer/Loader.h"
#include "../Models/RawModel.h"
#include "../Textures/ModelTexture.h"

class Terrain
{
public:
	Terrain(int InGridX, int InGridZ, Loader InModelLoader, ModelTexture InTexture);

	RawModel GetModel() { return Model; }
	ModelTexture GetTexture() { return Texture; }
	float GetX() { return X; }
	float GetZ() { return Z; }

private:
	RawModel GenerateTerrain(Loader InModelLoader);

	float X;
	float Z;

	RawModel Model;
	ModelTexture Texture;

	static float SIZE;
	static float VERTEX_COUNT;
};