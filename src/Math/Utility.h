#pragma once

#include <cmath>

namespace Math
{
	static float FLOAT_PI = 3.1415926535897932f; /* Extra digits if needed: 3.1415926535897932384626433832795f */
	static double DOUBLE_PI = 3.141592653589793238462643383279502884197169399;

	template <typename T>
	static inline T ToRadians(T const InDeg)
	{
		return InDeg * (DOUBLE_PI / 180.f);
	}

	template <typename T>
	static inline T ToDegrees(T const InRad)
	{
		return (InRad * 180.f) / (DOUBLE_PI);
	}
} // namespace Math