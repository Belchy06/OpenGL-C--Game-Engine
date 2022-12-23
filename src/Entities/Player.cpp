#include "Player.h"
#include "../Engine/Engine.h"
#include "../Delegates/Delegate.h"

unsigned int DelegateHandle::CURRENT_ID = 0;

Player::Player(TexturedModel InModel, Vector3<float> InPosition, Rotator<float> InRotation, Vector3<float> InScale)
	: Entity(InModel, InPosition, InRotation, InScale)
	, CurrentHorizontalSpeed(0)
	, CurrentVerticalSpeed(0)
	, CurrentTurnSpeed(0)
	, TerrainHeight(0)
	, bIsInAir(false)
	, SpringArm(-50)
	, PlayerCamera()
{
	Engine::MouseMove.AddRaw(this, &Player::HandleMouseMove);
	Engine::MouseWheel.AddRaw(this, &Player::HandleMouseWheel);
	Engine::KeyDown.AddRaw(this, &Player::HandleKeyDown);
	Engine::KeyUp.AddRaw(this, &Player::HandleKeyUp);

	SpringArm.SetupAttachment(this);
	PlayerCamera.SetupAttachment(&SpringArm);
}

void Player::Tick(float InDeltaTime)
{
	for (std::map<int, bool>::iterator Iter = Keys.begin(); Iter != Keys.end(); ++Iter)
	{
		if (!Iter->second)
		{
			continue;
		}
		switch (Iter->first)
		{
			case GLFW_KEY_W:
				CurrentHorizontalSpeed = -Engine::OPTIONS["PlayerRunSpeed"];
				break;
			case GLFW_KEY_S:
				CurrentHorizontalSpeed = +Engine::OPTIONS["PlayerRunSpeed"];
				break;
			case GLFW_KEY_A:
				CurrentTurnSpeed = Engine::OPTIONS["PlayerTurnSpeed"];
				break;
			case GLFW_KEY_D:
				CurrentTurnSpeed = -Engine::OPTIONS["PlayerTurnSpeed"];
				break;
			case GLFW_KEY_LEFT_CONTROL:

				Position += Vector3<float>(0.f, -Engine::OPTIONS["PlayerRunSpeed"], 0.f);
				break;
			case GLFW_KEY_SPACE:
				if (bIsInAir)
					break;
				CurrentVerticalSpeed = Engine::OPTIONS["JumpPower"];
				bIsInAir = true;
				break;
		}
	}

	Rotation += Rotator<float>(0, CurrentTurnSpeed * InDeltaTime, 0);
	float Distance = CurrentHorizontalSpeed * InDeltaTime;
	float DX = Distance * sin(Rotation.Y);
	float DZ = Distance * cos(Rotation.Y);
	Position += Vector3<float>(DX, 0, DZ);

	CurrentHorizontalSpeed = 0;
	CurrentTurnSpeed = 0;
	CurrentVerticalSpeed += Engine::OPTIONS["Gravity"] * InDeltaTime;
	Position += Vector3<float>(0, CurrentVerticalSpeed * InDeltaTime, 0);
	if (Position.Y < TerrainHeight)
	{
		CurrentVerticalSpeed = 0.f;
		bIsInAir = false;
		Position = Vector3<float>(Position.X, TerrainHeight, Position.Z);
	}
}

void Player::HandleKeyDown(int InKey)
{
	if (InKey != -1)
	{
		Keys[InKey] = true;
	}
}

void Player::HandleKeyUp(int InKey)
{
	if (InKey != -1)
	{
		Keys[InKey] = false;
	}
}

// void Player::HandleMouseButton()
// {
// }

void Player::HandleMouseWheel(double InDelta)
{
	float ZoomLevel = InDelta * 2.f;
	SpringArm.FollowDistance -= ZoomLevel;
	if (SpringArm.FollowDistance < 0.f)
	{
		SpringArm.FollowDistance = 0.f;
	}
}

void Player::HandleMouseMove(Vector2<double> InMousePos, Vector2<double> InDelta)
{
}