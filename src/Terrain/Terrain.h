#pragma once

#include "../Containers/Array.h"
#include "../Renderer/Loader.h"
#include "../Models/RawModel.h"
#include "../Textures/TerrainTexture.h"
#include "../Textures/TerrainTexturePack.h"

class Terrain
{
public:
	Terrain(int InGridX, int InGridZ, Loader InModelLoader, TerrainTexture InBlendMap, TerrainTexturePack InTexturePack);

	RawModel GetModel() { return Model; }
	TerrainTexturePack GetTexturePack() { return TexturePack; }
	TerrainTexture GetBlendMap() { return BlendMap; }
	float GetX() { return X; }
	float GetZ() { return Z; }

private:
	RawModel GenerateTerrain(Loader InModelLoader);

	float X;
	float Z;

	RawModel Model;
	TerrainTexture BlendMap;
	TerrainTexturePack TexturePack;

	static float SIZE;
	static float VERTEX_COUNT;
};