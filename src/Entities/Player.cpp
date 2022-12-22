#include "Player.h"
#include "../Engine/Engine.h"

Player::Player(TexturedModel InModel, Vector3<float> InPosition, Rotator<float> InRotation, Vector3<float> InScale)
	: Entity(InModel, InPosition, InRotation, InScale)
	, CurrentHorizontalSpeed(0)
	, CurrentVerticalSpeed(0)
	, CurrentTurnSpeed(0)
	, TerrainHeight(0)
	, bIsInAir(false)
{
}

void Player::Tick(float DeltaTime)
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
				CurrentHorizontalSpeed = Engine::OPTIONS["PlayerRunSpeed"];
				break;
			case GLFW_KEY_S:
				CurrentHorizontalSpeed = -Engine::OPTIONS["PlayerRunSpeed"];
				break;
			case GLFW_KEY_A:
				CurrentTurnSpeed = Engine::OPTIONS["PlayerTurnSpeed"];
				break;
			case GLFW_KEY_D:
				CurrentTurnSpeed = -Engine::OPTIONS["PlayerTurnSpeed"];
				break;
			case GLFW_KEY_LEFT_CONTROL:

				IncreasePosition(Vector3<float>(0.f, -Engine::OPTIONS["PlayerRunSpeed"], 0.f));
				break;
			case GLFW_KEY_SPACE:
				if (bIsInAir)
					break;
				CurrentVerticalSpeed = Engine::OPTIONS["JumpPower"];
				bIsInAir = true;
				break;
		}
	}

	IncreaseRotation(Rotator<float>(0, CurrentTurnSpeed * DeltaTime, 0));
	float Distance = CurrentHorizontalSpeed * DeltaTime;
	float DX = Distance * sin(GetRotation().Y);
	float DZ = Distance * cos(GetRotation().Y);
	IncreasePosition(Vector3<float>(DX, 0, DZ));

	CurrentHorizontalSpeed = 0;
	CurrentTurnSpeed = 0;
	CurrentVerticalSpeed += Engine::OPTIONS["Gravity"] * DeltaTime;
	IncreasePosition(Vector3<float>(0, CurrentVerticalSpeed * DeltaTime, 0));
	if (GetPosition().Y < TerrainHeight)
	{
		CurrentVerticalSpeed = 0.f;
		bIsInAir = false;
		SetPosition(Vector3<float>(GetPosition().X, TerrainHeight, GetPosition().Z));
	}
}

void Player::HandleKeyDown(int Key)
{
	if (Key != -1)
	{
		Keys[Key] = true;
	}
}

void Player::HandleKeyUp(int Key)
{
	if (Key != -1)
	{
		Keys[Key] = false;
	}
}