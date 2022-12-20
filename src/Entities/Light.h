#pragma once

#include "../Math/Vector.h"

class Light
{
public:
	Light(Vector3<float> InPosition, Vector3<float> InColour);

	Vector3<float> GetColour() { return Colour; }
	void SetColour(Vector3<float> InColour) { Colour = InColour; }

	Vector3<float> GetPosition() { return Position; }
	void SetPosition(Vector3<float> InPosition) { Position = InPosition; }

private:
	Vector3<float> Position;
	Vector3<float> Colour;
};