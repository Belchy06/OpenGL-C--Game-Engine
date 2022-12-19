#pragma once

#include "RawModel.h"
#include "../Textures/ModelTexture.h"

class TexturedModel
{
public:
	TexturedModel(RawModel InModel, ModelTexture InTexture);
	RawModel GetRawModel();
	ModelTexture GetModelTexture();

private:
	RawModel Model;
	ModelTexture Texture;
};