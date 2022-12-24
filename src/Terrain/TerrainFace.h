#pragma once

#include "Terrain.h"

class TerrainFace : public Terrain
{
public:
	TerrainFace(int InGridX, int InGridZ, Loader InModelLoader, TerrainTexture InBlendMap, TerrainTexturePack InTexturePack, Vector3<float> InLocalUp);

private:
	virtual RawModel GenerateTerrain(Loader InModelLoader);

	Vector3<float> LocalUp;
	Vector3<float> AxisA;
	Vector3<float> AxisB;

	static float SIZE;
	static float VERTEX_COUNT;
};