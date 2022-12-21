#pragma once

#include "TerrainTexture.h"

class TerrainTexturePack
{
public:
	TerrainTexturePack(TerrainTexture InBackgroundTexture, TerrainTexture InRTexture, TerrainTexture InGTexture, TerrainTexture InBTexture);

	TerrainTexture GetBackgroundTexture() { return BackgroundTexture; }
	TerrainTexture GetRTexture() { return RTexture; }
	TerrainTexture GetGTexture() { return GTexture; }
	TerrainTexture GetBTexture() { return BTexture; }

private:
	TerrainTexture BackgroundTexture;
	TerrainTexture RTexture;
	TerrainTexture GTexture;
	TerrainTexture BTexture;
};
