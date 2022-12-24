#include "Input.h"
#include "../Engine/Engine.h"
#include "../Delegates/Delegate.h"

unsigned int DelegateHandle::CURRENT_ID = 0;

InputComponent::InputComponent()
	: Object()
{
	Engine::MouseMove.AddRaw(this, &InputComponent::HandleMouseMove);
	Engine::MouseWheel.AddRaw(this, &InputComponent::HandleMouseWheel);
	Engine::KeyDown.AddRaw(this, &InputComponent::HandleKeyDown);
	Engine::KeyUp.AddRaw(this, &InputComponent::HandleKeyUp);
}

void InputComponent::Tick(float InDeltaTime)
{
	float CurrentHorizontalSpeed, CurrentTurnSpeed;
	CurrentHorizontalSpeed = 0.f;
	CurrentTurnSpeed = 0.f;

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
			case GLFW_KEY_LEFT_SHIFT:
				bIsWireframe = !bIsWireframe;
				MasterRenderer::SetWireframe(bIsWireframe);
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
}

void InputComponent::HandleKeyDown(int InKey)
{
	if (InKey != -1)
	{
		Keys[InKey] = true;
	}
}

void InputComponent::HandleKeyUp(int InKey)
{
	if (InKey != -1)
	{
		Keys[InKey] = false;
	}
}

// void Player::HandleMouseButton()
// {
// }

void InputComponent::HandleMouseWheel(double InDelta)
{
	ZoomLevel -= InDelta * 2.f;
}

void InputComponent::HandleMouseMove(Vector2<double> InMousePos, Vector2<double> InDelta)
{
}