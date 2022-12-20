#include "Camera.h"

Camera::Camera()
	: Position(Vector3<float>::ZeroVector())
	, Rotation(Rotator<float>(0.f))
{
}

Camera::Camera(Vector3<float> InPosition, Rotator<float> InRotation)
	: Position(InPosition)
	, Rotation(InRotation)
{
}