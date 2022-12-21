#include "Camera.h"

Camera::Camera()
	: Position(Vector3<float>::ZeroVector())
	, Rotation(Rotator<float>::ZeroRotator())
{
}

Camera::Camera(Vector3<float> InPosition, Rotator<float> InRotation)
	: Position(InPosition)
	, Rotation(InRotation)
{
}

Matrix4<float> Camera::GetTransformationMatrix()
{
	Vector3<float> CameraPosition = Position * -1;
	Vector3<float> CameraScale = Vector3<float>::OneVector();
	Rotator<float> CameraRotation = Rotation;
	Transform<float> ViewTransform(CameraPosition, CameraScale, CameraRotation);
	return ViewTransform.ToMatrix();
}