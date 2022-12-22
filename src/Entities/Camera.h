#pragma once

#include "Object.h"

#include "../Math/Vector.h"
#include "../Math/Rotator.h"
#include "../Math/Matrix.h"
#include "../Math/Transform.h"

#include "../ThirdParty/glfw-3.3.8/include/GLFW/glfw3.h"

class Camera : public Object
{
public:
	Camera();
	Camera(Vector3<float> InPosition, Rotator<float> InRotation);

	Matrix4<float> GetTransformationMatrix();
};