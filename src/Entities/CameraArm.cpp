#include "CameraArm.h"

#include "../ThirdParty/glm/include/gtx/matrix_decompose.hpp"
#include "../ThirdParty/glm/include/gtc/matrix_transform.hpp"

CameraArm::CameraArm(float InFollowDistance)
	: FollowDistance(InFollowDistance)
{
}

void CameraArm::Tick(float InDeltaTime)
{
	if (Attachment != nullptr)
	{
		UpdatePositon(Attachment->Position, Attachment->Rotation);
	}
}

void CameraArm::SetupAttachment(Object* InAttachment)
{
	if (InAttachment != nullptr)
	{
		Attachment = InAttachment;
		UpdatePositon(InAttachment->Position, InAttachment->Rotation);
	}
}

void CameraArm::UpdatePositon(Vector3<float> InPosition, Rotator<float> InRotator)
{
	float HorizontalDistance = FollowDistance * cos(InRotator.X);
	float DeltaZ = HorizontalDistance * cos(InRotator.Y);
	Position.Z = InPosition.Z - DeltaZ;

	float DeltaX = HorizontalDistance * sin(InRotator.Y);
	Position.X = InPosition.X - DeltaX;

	float VerticalDistance = FollowDistance * sin(InRotator.X);
	Position.Y = InPosition.Y - VerticalDistance + 10;
}

Matrix4<float> CameraArm::GetTransformationMatrix()
{
	glm::mat4 Matrix = glm::lookAt(glm::vec3(Position.X, Position.Y, Position.Z), glm::vec3(Attachment->Position.X, Attachment->Position.Y, Attachment->Position.Z), glm::vec3(0, 1, 0));
	Matrix4<float> Mat;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Mat.GetData()[i * 4 + j] = Matrix[i][j];
		}
	}

	return Mat;
}