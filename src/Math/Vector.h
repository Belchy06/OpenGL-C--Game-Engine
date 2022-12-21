#pragma once

#include <initializer_list>
#include "../Containers/Array.h"
template <typename T>
class Vector2
{
public:
	static Vector2<T> ZeroVector() { return Vector2<T>(0.f, 0.f); }
	static Vector2<T> OneVector() { return Vector2<T>(1.f, 1.f); }

	Vector2()
		: X(0), Y(0) {}

	Vector2(T InValue)
		: X(InValue), Y(InValue) {}

	Vector2(T InX, T InY)
		: X(InX), Y(InY) {}

	Vector2(Array<T> InData)
		: X(InData[0]), Y(InData[1]) {}

	Vector2(std::initializer_list<T> List)
	{
		if (List.size() == 2)
		{
			int idx = 0;
			for (const T Item : List)
			{
				switch (idx)
				{
					case 0:
						X = Item;
						break;
					case 1:
						Y = Item;
						break;
				}
				idx++;
			}
		}
	}

	Vector2<T> operator-(const Vector2<T>& Other)
	{
		return Vector2<T>(X - Other.X, Y - Other.Y, Z - Other.Z);
	}

	Vector2<T> operator-=(const Vector2<T>& Other)
	{
		*this = *this - Other;
	}

	Vector2<T> operator+(const Vector2<T>& Other)
	{
		return Vector2<T>(X + Other.X, Y + Other.Y);
	}

	Vector2<T> operator*(const float Scalar) const
	{
		return Vector2<T>(X * Scalar, Y * Scalar);
	}

	void operator+=(const Vector2<T>& Other)
	{
		*this = *this + Other;
	}

	T X;
	T Y;
};

template <typename T>
class Vector3
{
public:
	static Vector3<T> ZeroVector() { return Vector3<T>(0.f, 0.f, 0.f); }
	static Vector3<T> OneVector() { return Vector3<T>(1.f, 1.f, 1.f); }

	Vector3()
		: X(0), Y(0), Z(0) {}

	Vector3(T InValue)
		: X(InValue), Y(InValue), Z(InValue) {}

	Vector3(T InX, T InY, T InZ)
		: X(InX), Y(InY), Z(InZ) {}

	Vector3(Array<T> InData)
		: X(InData[0]), Y(InData[1]), Z(InData[2]) {}

	Vector3(std::initializer_list<T> List)
	{
		if (List.size() == 3)
		{
			int idx = 0;
			for (const T Item : List)
			{
				switch (idx)
				{
					case 0:
						X = Item;
						break;
					case 1:
						Y = Item;
						break;
					case 2:
						Z = Item;
						break;
				}
				idx++;
			}
		}
	}

	Vector3<T> operator-(const Vector3<T>& Other)
	{
		return Vector3<T>(X - Other.X, Y - Other.Y, Z - Other.Z);
	}

	Vector3<T> operator-=(const Vector3<T>& Other)
	{
		*this = *this - Other;
	}

	Vector3<T> operator+(const Vector3<T>& Other)
	{
		return Vector3<T>(X + Other.X, Y + Other.Y, Z + Other.Z);
	}

	Vector3<T> operator*(const float Scalar) const
	{
		return Vector3<T>(X * Scalar, Y * Scalar, Z * Scalar);
	}

	void operator+=(const Vector3<T>& Other)
	{
		*this = *this + Other;
	}

	T X;
	T Y;
	T Z;
};

template <typename T>
class Vector4
{
public:
	static Vector4<T> ZeroVector() { return Vector4<T>(0.f, 0.f, 0.f, 0.f); }

	Vector4()
		: X(0), Y(0), Z(0), W(0) {}

	Vector4(T InValue)
		: X(InValue), Y(InValue), Z(InValue), W(InValue)
	{
	}

	Vector4(T InX, T InY, T InZ, T InW)
		: X(InX), Y(InY), Z(InZ), W(InW) {}

	Vector4(Array<T> InData)
		: X(InData[0]), Y(InData[1]), Z(InData[2]), W(InData[3]) {}

	Vector4(std::initializer_list<T> List)
	{
		if (List.size() == 4)
		{
			int idx = 0;
			for (const T Item : List)
			{
				switch (idx)
				{
					case 0:
						X = Item;
						break;
					case 1:
						Y = Item;
						break;
					case 2:
						Z = Item;
						break;
					case 3:
						W = Item;
						break;
				}
				idx++;
			}
		}
	}

	Vector4<T> operator+(const Vector4<T>& Other)
	{
		return Vector4<T>(X + Other.X, Y + Other.Y, Z + Other.Z, W + Other.W);
	}

	void operator+=(const Vector4<T>& Other)
	{
		*this = *this + Other;
	}

	T X;
	T Y;
	T Z;
	T W;
};
