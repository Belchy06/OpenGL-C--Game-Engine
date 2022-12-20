#pragma once

#include "../Math/Vector.h"
#include "../Math/Rotator.h"
#include "../Math/Matrix.h"
#include "../Math/Transform.h"

#include "../ThirdParty/glfw-3.3.8/include/GLFW/glfw3.h"

class Camera
{
public:
	Camera();
	Camera(Vector3<float> InPosition, Rotator<float> InRotation);

	Vector3<float> GetPosition() { return Position; }
	void SetPosition(Vector3<float> InPosition) { Position = InPosition; }
	void IncreasePosition(Vector3<float> InDelta) { Position += InDelta; }

	Rotator<float> GetRotation() { return Rotation; }
	void SetRotation(Rotator<float> InRotation) { Rotation = InRotation; }
	void IncreaseRotation(Rotator<float> InDelta) { Rotation += InDelta; }

	Matrix4<float> GetTransformationMatrix();

private:
	Vector3<float> Position;
	Rotator<float> Rotation;
};