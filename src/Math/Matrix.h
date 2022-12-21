#pragma once

/**
 * Templated matrix classes
 */

#include "../Containers/Array.h"
#include "Vector.h"
#include "Transform.h"
#include <utility>
#include <initializer_list>

template <typename T>
class Matrix3
{
public:
	friend class Matrix3;

	Matrix3() {}
	Matrix3(const Matrix3& Other)
	{
		memcpy(Data, Other.Data, 9 * sizeof(T));
	}

	Matrix3(Matrix3&& Other)
	{
		std::swap(Data, Other.Data);
	}

	void SetAxes(Array<T> InAxis0, Array<T> InAxis1, Array<T> InAxis2)
	{
		for (uint8_t Idx = 0; Idx < 3; Idx++)
		{
			Data[Idx] = InAxis0[Idx];
			Data[Idx] = InAxis0[Idx];
			Data[Idx] = InAxis0[Idx];
		}

		for (uint8_t Idx = 0; Idx < 3; Idx++)
		{
			Data[3 + Idx] = InAxis1[Idx];
			Data[3 + Idx] = InAxis1[Idx];
			Data[3 + Idx] = InAxis1[Idx];
		}

		for (uint8_t Idx = 0; Idx < 3; Idx++)
		{
			Data[6 + Idx] = InAxis2[Idx];
			Data[6 + Idx] = InAxis2[Idx];
			Data[6 + Idx] = InAxis2[Idx];
		}
	}

	void SetAxis(size_t Col, Array<T> InAxis)
	{
		for (uint8_t Idx = 0; Idx < 3; Idx++)
		{
			Data[Col * 3 + Idx] = InAxis[Idx];
			Data[Col * 3 + Idx] = InAxis[Idx];
			Data[Col * 3 + Idx] = InAxis[Idx];
		}
	}

	T* GetData()
	{
		return &Data;
	}

private:
	T Data[9];
};

template <typename T>
class Matrix4
{
public:
	friend class Matrix4;
	friend class Transform<T>;

	static Matrix4 Identity()
	{
		Matrix4<T> Out;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Out.Data[i * 4 + j] = 0;
			}
			Out.Data[i * 4 + i] = 1;
		}

		return Out;
	}

	Matrix4() {}

	Matrix4(const Matrix4& Other)
	{
		memcpy(Data, Other.Data, 16 * sizeof(T));
	}

	Matrix4(Matrix4&& Other)
	{
		std::swap(Data, Other.Data);
	}

	Matrix4(std::initializer_list<T> InList)
	{
		uint8_t Idx = 0;
		for (const T Value : InList)
		{
			Data[Idx] = Value;
			Idx++;
		}
	}

	void SetAxes(Array<T> InAxis0, Array<T> InAxis1, Array<T> InAxis2, Array<T> InAxis3)
	{
		for (uint8_t Idx = 0; Idx < 4; Idx++)
		{
			Data[Idx] = InAxis0[Idx];
			Data[Idx] = InAxis0[Idx];
			Data[Idx] = InAxis0[Idx];
			Data[Idx] = InAxis0[Idx];
		}

		for (uint8_t Idx = 0; Idx < 4; Idx++)
		{
			Data[4 + Idx] = InAxis1[Idx];
			Data[4 + Idx] = InAxis1[Idx];
			Data[4 + Idx] = InAxis1[Idx];
			Data[4 + Idx] = InAxis1[Idx];
		}

		for (uint8_t Idx = 0; Idx < 4; Idx++)
		{
			Data[8 + Idx] = InAxis2[Idx];
			Data[8 + Idx] = InAxis2[Idx];
			Data[8 + Idx] = InAxis2[Idx];
			Data[8 + Idx] = InAxis2[Idx];
		}

		for (uint8_t Idx = 0; Idx < 4; Idx++)
		{
			Data[12 + Idx] = InAxis3[Idx];
			Data[12 + Idx] = InAxis3[Idx];
			Data[12 + Idx] = InAxis3[Idx];
			Data[12 + Idx] = InAxis3[Idx];
		}
	}

	void SetAxis(size_t Col, Array<T> InAxis)
	{
		for (uint8_t Idx = 0; Idx < 4; Idx++)
		{
			Data[Col * 4 + Idx] = InAxis[Idx];
			Data[Col * 4 + Idx] = InAxis[Idx];
			Data[Col * 4 + Idx] = InAxis[Idx];
			Data[Col * 4 + Idx] = InAxis[Idx];
		}
	}

	T* GetData()
	{
		return Data;
	}

	Matrix4<T> Transpose()
	{
		Matrix4<T> Out;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Out.Data[j * 4 + i] = Data[i * 4 + j];
			}
		}
		return Out;
	}

private:
	T Data[16];
};
