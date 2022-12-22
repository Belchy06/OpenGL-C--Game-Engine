#pragma once

#include "Object.h"
#include "../Math/Vector.h"
#include "../Math/Rotator.h"
#include "../Models/TexturedModel.h"

class Entity : public Object
{
public:
	Entity(TexturedModel InModel, Vector3<float> InPosition, Rotator<float> InRotation, Vector3<float> InScale);
	TexturedModel GetModel() { return Model; }

private:
	TexturedModel Model;
};