#pragma once

/**
 * Templated Rotator class. Wraps a Vector3 to provide some additonal methods for conversion to Quaternions
 *
 * NOTE: Values are in degrees
 */

#include "Vector.h"
#include "Quaternion.h"
#include <cmath>
#include "Utility.h"

template <typename T>
class Quaternion;

template <typename T>
class Rotator : public Vector3<T>
{
public:
	static Rotator<T> ZeroRotator() { return Rotator<T>(0.f); }

	Rotator(T InValue)
		: Vector3(InValue)
	{
	}

	Rotator(T InX, T InY, T InZ)
		: Vector3(InX, InY, InZ)
	{
	}

	Rotator<T> operator*(const float Scalar) const
	{
		return Rotator<T>(X * Scalar, Y * Scalar, Z * Scalar);
	}

	Quaternion<T> Quat()
	{
		double cr = cos(X * 0.5);
		double sr = sin(X * 0.5);
		double cp = cos(Y * 0.5);
		double sp = sin(Y * 0.5);
		double cy = cos(Z * 0.5);
		double sy = sin(Z * 0.5);

		Quaternion<T> Q;
		Q.W = cr * cp * cy + sr * sp * sy;
		Q.X = sr * cp * cy - cr * sp * sy;
		Q.Y = cr * sp * cy + sr * cp * sy;
		Q.Z = cr * cp * sy - sr * sp * cy;

		return Q;
	}
};