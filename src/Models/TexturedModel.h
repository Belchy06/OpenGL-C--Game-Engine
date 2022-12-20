#pragma once

#include "RawModel.h"
#include "../Textures/ModelTexture.h"

class TexturedModel
{
public:
	TexturedModel(RawModel InModel, ModelTexture InTexture);
	RawModel GetRawModel() const { return Model; }
	ModelTexture GetModelTexture() const { return Texture; }

private:
	RawModel Model;
	ModelTexture Texture;
};