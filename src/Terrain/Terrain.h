#pragma once

#include "../Entities/Object.h"
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

	Vector3<float> Position;
	Rotator<float> Rotation;
	Vector3<float> Scale;

private:
	RawModel GenerateTerrain(Loader InModelLoader);

	RawModel Model;
	TerrainTexture BlendMap;
	TerrainTexturePack TexturePack;

	static float SIZE;
	static float VERTEX_COUNT;
};