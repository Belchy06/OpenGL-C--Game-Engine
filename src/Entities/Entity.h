#pragma once

#include "../Math/Vector.h"
#include "../Math/Rotator.h"
#include "../Models/TexturedModel.h"

class Entity
{
public:
	Entity(TexturedModel InModel,
		Vector3<float> InPosition,
		Rotator<float> InRotation,
		Vector3<float> InScale);

	void IncreasePosition(Vector3<float> Delta);
	void IncreaseRotation(Vector3<float> Delta);

	Vector3<float> GetPosition() { return Position; }
	TexturedModel GetModel() { return Model; }
	Rotator<float> GetRotation() { return Rotation; }
	Vector3<float> GetScale() { return Scale; }

private:
	Vector3<float> Position;
	TexturedModel Model;
	Rotator<float> Rotation;
	Vector3<float> Scale;
};