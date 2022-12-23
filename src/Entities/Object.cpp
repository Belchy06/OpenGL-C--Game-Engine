#include "Object.h"
#include "../Engine/Engine.h"

Object::~Object()
{
	Engine::Objects.erase(this);
}

Object::Object()
	: Position(Vector3<float>::ZeroVector())
	, Rotation(Rotator<float>::ZeroRotator())
	, Scale(Vector3<float>::OneVector())
{
	Engine::Objects.insert(this);
}

Object::Object(Vector3<float> InPosition)
	: Position(InPosition)
	, Rotation(Rotator<float>::ZeroRotator())
	, Scale(Vector3<float>::OneVector())
{
	Engine::Objects.insert(this);
}

Object::Object(Rotator<float> InRotation)
	: Position(Vector3<float>::ZeroVector())
	, Rotation(InRotation)
	, Scale(Vector3<float>::OneVector())
{
	Engine::Objects.insert(this);
}

Object::Object(Vector3<float> InPosition, Rotator<float> InRotation)
	: Position(InPosition)
	, Rotation(InRotation)
	, Scale(Vector3<float>::OneVector())
{
	Engine::Objects.insert(this);
}

Object::Object(Vector3<float> InPosition, Rotator<float> InRotation, Vector3<float> InScale)
	: Position(InPosition)
	, Rotation(InRotation)
	, Scale(InScale)
{
	Engine::Objects.insert(this);
}

void Object::SetupAttachment(Object* InAttachment)
{
	Attachment = InAttachment;
	Position = InAttachment->Position;
	Rotation = InAttachment->Rotation;
}

void Object::Tick(float InDeltaTime)
{
	if (Attachment != nullptr && bCanTick)
	{
		Position = Attachment->Position;
		Rotation = Attachment->Rotation;
	}
}