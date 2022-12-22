#pragma once

#include "Object.h"
#include "../Math/Vector.h"

class Light : public Object
{
public:
	Light(Vector3<float> InPosition, Vector3<float> InColour);

	Vector3<float> GetColour() { return Colour; }
	void SetColour(Vector3<float> InColour) { Colour = InColour; }

private:
	Vector3<float> Colour;
};