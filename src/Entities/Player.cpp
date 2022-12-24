#include "Player.h"

Player::Player(TexturedModel InModel, Vector3<float> InPosition, Rotator<float> InRotation, Vector3<float> InScale)
	: Entity(InModel, InPosition, InRotation, InScale)
	, TerrainHeight(0)
	, SpringArm(-50)
	, PlayerCamera()
	, Input()
{
	SpringArm.SetupAttachment(this);
	PlayerCamera.SetupAttachment(&SpringArm);

	Input.SetupAttachment(this);
	Input.ZoomLevel = -SpringArm.FollowDistance;
}

void Player::Tick(float InDeltaTime)
{
	Position = Input.Position;
	Rotation = Input.Rotation;

	SpringArm.FollowDistance = Input.ZoomLevel;
	if (SpringArm.FollowDistance < 0.1f)
	{
		SpringArm.FollowDistance = 0.1f;
	}

	if (Position.Y < TerrainHeight)
	{
		Input.CurrentVerticalSpeed = 0.f;
		Input.bIsInAir = false;
		Position = Vector3<float>(Position.X, TerrainHeight, Position.Z);
	}
}