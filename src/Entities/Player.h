#pragma once

#include <cmath>
#include <map>

#include "Entity.h"

#include "../ThirdParty/glfw-3.3.8/include/GLFW/glfw3.h"

class Player : public Entity
{
public:
	Player(TexturedModel InModel, Vector3<float> InPosition, Rotator<float> InRotation, Vector3<float> InScale);

	void HandleKeyDown(int Key);
	void HandleKeyUp(int Key);
	void Tick(float DeltaTime);

	void SetTerrainHeight(float InTerrainHeight) { TerrainHeight = InTerrainHeight; }

private:
	bool bIsInAir;
	float TerrainHeight;
	float CurrentHorizontalSpeed;
	float CurrentTurnSpeed;
	float CurrentVerticalSpeed;

	std::map<int, bool> Keys;

	static float RUN_SPEED;
	static float TURN_SPEED;
};