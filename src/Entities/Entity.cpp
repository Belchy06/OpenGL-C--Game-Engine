#include "Entity.h"

Entity::Entity(TexturedModel InModel, Vector3<float> InPosition, Rotator<float> InRotation, Vector3<float> InScale)
	: Object(InPosition, InRotation, InScale)
	, Model(InModel)
{
}