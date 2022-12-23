#pragma once

#include <cmath>

#include "../Math/Utility.h"
#include "Object.h"
#include "Camera.h"

class CameraArm : public Object
{
public:
	CameraArm(float InFollowDistance);

	virtual void SetupAttachment(Object* InAttachment) override;
	virtual void Tick(float InDeltaTime) override;

	Matrix4<float> GetTransformationMatrix();

	float FollowDistance;

private:
	void UpdatePositon(Vector3<float> InPosition, Rotator<float> InRotator);
};