#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(Vector3<float> InPosition, Rotator<float> InRotation)
	: Object(InPosition, InRotation)
{
}

Matrix4<float> Camera::GetTransformationMatrix()
{
	Vector3<float> CameraPosition = GetPosition() * -1;
	Vector3<float> CameraScale = Vector3<float>::OneVector();
	Rotator<float> CameraRotation = GetRotation();
	Transform<float> ViewTransform(CameraPosition, CameraScale, CameraRotation);
	return ViewTransform.ToMatrix();
}