#pragma once

#include <cmath>
#include <map>

#include "Entity.h"
#include "CameraArm.h"

#include "../ThirdParty/glfw-3.3.8/include/GLFW/glfw3.h"

class Player : public Entity
{
public:
	Player(TexturedModel InModel, Vector3<float> InPosition, Rotator<float> InRotation, Vector3<float> InScale);

	void HandleKeyDown(int InKey);
	void HandleKeyUp(int InKey);
	void HandleMouseMove(Vector2<double> InMousePos, Vector2<double> InDelta);
	void HandleMouseWheel(double InDelta);
	void SetTerrainHeight(float InTerrainHeight) { TerrainHeight = InTerrainHeight; }

	virtual void Tick(float InDeltaTime) override;

	Camera PlayerCamera;
	CameraArm SpringArm;

private:
	bool bIsInAir;
	float TerrainHeight;
	float CurrentHorizontalSpeed;
	float CurrentTurnSpeed;
	float CurrentVerticalSpeed;

	std::map<int, bool> Keys;
};