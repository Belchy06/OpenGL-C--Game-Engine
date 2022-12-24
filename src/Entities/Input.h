#pragma once

#include "Object.h"
#include <map>

class InputComponent : public Object
{
public:
	InputComponent();

	void HandleKeyDown(int InKey);
	void HandleKeyUp(int InKey);
	void HandleMouseMove(Vector2<double> InMousePos, Vector2<double> InDelta);
	void HandleMouseWheel(double InDelta);

	virtual void Tick(float InDeltaTime) override;

	float ZoomLevel = 0.f;
	bool bIsInAir = false;
	float CurrentVerticalSpeed = 0.f;

private:
	std::map<int, bool> Keys;

	bool bIsWireframe = false;
};
