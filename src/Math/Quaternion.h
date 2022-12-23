#pragma once

/**
 * Templated Quaternion class. Wraps a Vector4 to provide some additonal methods for conversion to Euler angles
 *
 * * NOTE: Values are in radians
 */

#include "Vector.h"
#include "Rotator.h"

template <typename T>
class Rotator;

template <typename T>
class Quaternion : public Vector4<T>
{
public:
	Quaternion() {}
	Quaternion(const Quaternion& Other)
	{
		X = Other.X;
		Y = Other.Y;
		Z = Other.Z;
		W = Other.W;
	}
	Quaternion(T InX, T InY, T InZ, T InW)
		: Vector4(InX, InY, InZ, InW)
	{
	}

	Quaternion(Rotator<T> Rot)
	{
		*this = Rot.Quat();
	}

	static Quaternion<T>
	Identity()
	{
		return Quaternion<T>(0.f, 0.f, 0.f, 1.f);
	}

	Quaternion<T> Inverse()
	{
		return Quaternion<T>(X * -1.f, Y * -1.f, Z * -1.f, W * 1.f);
	}

	Quaternion<T> operator*(const Vector3<T> Other) const
	{
		return Quaternion<T>(X * Other.X, Y * Other.Y, Z * Other.Z, W);
	}
};