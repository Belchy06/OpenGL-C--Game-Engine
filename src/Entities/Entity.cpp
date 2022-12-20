#include "Entity.h"

Entity::Entity(TexturedModel InModel, Vector3<float> InPosition, Rotator<float> InRotation, Vector3<float> InScale)
	: Model(InModel), Position(InPosition), Rotation(InRotation), Scale(InScale)
{
}

void Entity::IncreasePosition(Vector3<float> Delta)
{
	Position += Delta;
}

void Entity::IncreaseRotation(Vector3<float> Delta)
{
	Rotation += Delta;
}