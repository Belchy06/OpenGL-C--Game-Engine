#pragma once

#include <cmath>

namespace Math
{
#define FLOAT_PI (3.1415926535897932f) /* Extra digits if needed: 3.1415926535897932384626433832795f */
#define DOUBLE_PI (3.141592653589793238462643383279502884197169399)

	template <typename T>
	static inline T ToRadians(T const& InDeg)
	{
		return InDeg * (DOUBLE_PI / 180.f);
	}

	template <typename T>
	static inline T ToDegrees(T const& InRad)
	{
		return 180.f / (InRad * DOUBLE_PI);
	}
} // namespace Math