#pragma once

#include <map>
#include "../Math/Vector.h"
#include "../Math/Rotator.h"
#include "../Containers/Array.h"

class Object
{
public:
	Object();
	~Object();
	Object(Vector3<float> InPosition);
	Object(Rotator<float> InRotation);
	Object(Vector3<float> InPosition, Rotator<float> InRotation);
	Object(Vector3<float> InPosition, Rotator<float> InRotation, Vector3<float> InScale);

	virtual void SetupAttachment(Object* InAttachment);
	virtual void Tick(float InDeltaTime);

	Vector3<float> Position;
	Rotator<float> Rotation;
	Vector3<float> Scale;

	bool bCanTick = true;
	Object* Attachment = nullptr;
};
