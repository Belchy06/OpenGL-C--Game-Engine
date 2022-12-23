#pragma once

#include "../Containers/Array.h"
#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"
#include <utility>
#include <initializer_list>
#include <cmath>

template <typename T>
class Matrix4;

template <typename T>
class Transform
{
public:
	friend class Transform;

	static Transform<T> Identity() { return Transform<T>(Vector3<T>::ZeroVector(), Vector3<T>::OneVector(), Quaternion<T>::Identity()); }

	Transform()
		: Rotation(Quaternion<T>::Identity())
		, Translation(Vector3<T>::ZeroVector())
		, Scale(Vector3<T>::OneVector())
	{
	}

	Transform(Vector3<T> InTranslation, Vector3<T> InScale, Quaternion<T> InRotation)
		: Translation(InTranslation)
		, Rotation(InRotation)
		, Scale(InScale)
	{
	}

	Transform(Vector3<T> InTranslation, Vector3<T> InScale, Rotator<T> InRotation)
		: Translation(InTranslation)
		, Rotation(InRotation)
		, Scale(InScale)
	{
	}

	Matrix4<T> ToMatrix()
	{
		Matrix4<T> OutMatrix;

		OutMatrix.Data[12] = Translation.X;
		OutMatrix.Data[13] = Translation.Y;
		OutMatrix.Data[14] = Translation.Z;

		const T x2 = Rotation.X + Rotation.X;
		const T y2 = Rotation.Y + Rotation.Y;
		const T z2 = Rotation.Z + Rotation.Z;
		{
			const T xx2 = Rotation.X * x2;
			const T yy2 = Rotation.Y * y2;
			const T zz2 = Rotation.Z * z2;

			OutMatrix.Data[0] = (1.0f - (yy2 + zz2)) * Scale.X;
			OutMatrix.Data[5] = (1.0f - (xx2 + zz2)) * Scale.Y;
			OutMatrix.Data[10] = (1.0f - (xx2 + yy2)) * Scale.Z;
		}
		{
			const T yz2 = Rotation.Y * z2;
			const T wx2 = Rotation.W * x2;

			OutMatrix.Data[9] = (yz2 - wx2) * Scale.Z;
			OutMatrix.Data[6] = (yz2 + wx2) * Scale.Y;
		}
		{
			const T xy2 = Rotation.X * y2;
			const T wz2 = Rotation.W * z2;

			OutMatrix.Data[4] = (xy2 - wz2) * Scale.Y;
			OutMatrix.Data[1] = (xy2 + wz2) * Scale.X;
		}
		{
			const T xz2 = Rotation.X * z2;
			const T wy2 = Rotation.W * y2;

			OutMatrix.Data[8] = (xz2 + wy2) * Scale.Z;
			OutMatrix.Data[2] = (xz2 - wy2) * Scale.X;
		}

		OutMatrix.Data[3] = 0.0f;
		OutMatrix.Data[7] = 0.0f;
		OutMatrix.Data[11] = 0.0f;
		OutMatrix.Data[15] = 1.0f;

		return OutMatrix;
	}

	Transform<T> Inverse()
	{
		Quaternion<float> InvRotation = Rotation.Inverse();
		Vector3<float> InvScale = Vector3<float>(1.f / Scale.X, 1.f / Scale.Y, 1.f / Scale.Z);
		Quaternion<float> Temp = InvRotation * (InvScale * (Translation * -1.f));
		Vector3<float> InvTranslation = Vector3<float>(Temp.X, Temp.Y, Temp.Z);

		return Transform<T>(InvTranslation, InvScale, InvRotation);
	}

	void Rotate(T InRotAmout, Vector3<T> InRotAxis)
	{
		Rotation += Quaternion<float>(Rotator<float>(InRotAxis.X * InRotAmout, InRotAxis.Y * InRotAmout, InRotAxis.Z * InRotAmout));
	}

	void Translate(Vector3<T> InTranslation)
	{
		Translation += InTranslation;
	}

private:
	Vector3<T> Translation;
	Vector3<T> Scale;
	Quaternion<T> Rotation;
};
