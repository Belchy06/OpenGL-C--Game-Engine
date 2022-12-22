#include "Object.h"

Object::Object()
	: Position(Vector3<float>::ZeroVector())
	, Rotation(Rotator<float>::ZeroRotator())
	, Scale(Vector3<float>::OneVector())
{
}

Object::Object(Vector3<float> InPosition)
	: Position(InPosition)
	, Rotation(Rotator<float>::ZeroRotator())
	, Scale(Vector3<float>::OneVector())
{
}

Object::Object(Rotator<float> InRotation)
	: Position(Vector3<float>::ZeroVector())
	, Rotation(InRotation)
	, Scale(Vector3<float>::OneVector())
{
}

Object::Object(Vector3<float> InPosition, Rotator<float> InRotation)
	: Position(InPosition)
	, Rotation(InRotation)
	, Scale(Vector3<float>::OneVector())
{
}

Object::Object(Vector3<float> InPosition, Rotator<float> InRotation, Vector3<float> InScale)
	: Position(InPosition)
	, Rotation(InRotation)
	, Scale(InScale)
{
}