#pragma once

#include <cmath>
#include <map>

#include "Entity.h"
#include "CameraArm.h"
#include "Input.h"

#include "../ThirdParty/glfw-3.3.8/include/GLFW/glfw3.h"

class Player : public Entity
{
public:
	Player(TexturedModel InModel, Vector3<float> InPosition, Rotator<float> InRotation, Vector3<float> InScale);

	void SetTerrainHeight(float InTerrainHeight) { TerrainHeight = InTerrainHeight; }

	virtual void Tick(float InDeltaTime) override;

	Camera PlayerCamera;
	CameraArm SpringArm;
	InputComponent Input;

private:
	float TerrainHeight;
};