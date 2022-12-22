#pragma once

#include "../Math/Vector.h"
#include "../Math/Rotator.h"
#include "../Containers/Array.h"

class Object
{
public:
	Object();
	Object(Vector3<float> InPosition);
	Object(Rotator<float> InRotation);
	Object(Vector3<float> InPosition, Rotator<float> InRotation);
	Object(Vector3<float> InPosition, Rotator<float> InRotation, Vector3<float> InScale);

	Vector3<float> GetPosition() { return Position; }
	void SetPosition(Vector3<float> InPosition) { Position = InPosition; }
	void IncreasePosition(Vector3<float> InDelta) { Position += InDelta; }

	Rotator<float> GetRotation() { return Rotation; }
	void SetRotation(Rotator<float> InRotation) { Rotation = InRotation; }
	void IncreaseRotation(Rotator<float> InDelta) { Rotation += InDelta; }

	Vector3<float> GetScale() { return Scale; }
	void SetScale(Vector3<float> InScale) { Scale = InScale; }
	void IncreaseScale(Vector3<float> InDelta) { Scale += InDelta; }

	Array<Object> Components;

private:
	Vector3<float> Position;
	Rotator<float> Rotation;
	Vector3<float> Scale;
};
