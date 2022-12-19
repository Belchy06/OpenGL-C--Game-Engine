#include "TexturedModel.h"

TexturedModel::TexturedModel(RawModel InModel, ModelTexture InTexture)
	: Model(InModel)
	, Texture(InTexture)
{
}

RawModel TexturedModel::GetRawModel()
{
	return Model;
}

ModelTexture TexturedModel::GetModelTexture()
{
	return Texture;
}