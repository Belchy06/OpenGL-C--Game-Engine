#include "Camera.h"
#include "../ThirdParty/glm/include/glm.hpp"
#include "../ThirdParty/glm/include/gtc/matrix_transform.hpp"
#include "CameraArm.h"

Camera::Camera()
	: Object(Vector3<float>::ZeroVector(), Rotator<float>::ZeroRotator())
{
}

Camera::Camera(Vector3<float> InPosition, Rotator<float> InRotation)
	: Object(InPosition, InRotation)
{
}

Matrix4<float> Camera::GetTransformationMatrix()
{
	if (Attachment != nullptr)
	{
		CameraArm* SpringArm = static_cast<CameraArm*>(Attachment);
		return SpringArm->GetTransformationMatrix();
	}

	Vector3<float> CameraPosition = Position * -1.f;
	Vector3<float> CameraScale = Vector3<float>::OneVector();
	Rotator<float> CameraRotation = Rotation;
	Transform<float> ViewTransform(CameraPosition, CameraScale, CameraRotation);
	return ViewTransform.ToMatrix();
}