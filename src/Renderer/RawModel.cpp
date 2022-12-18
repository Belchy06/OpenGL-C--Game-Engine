#include "RawModel.h"

RawModel::RawModel(unsigned int InVaoId, int InVertexCount)
{
	this->VaoID = InVaoId;
	this->VertexCount = InVertexCount;
}

unsigned int RawModel::GetVaoId()
{
	return this->VaoID;
}

int RawModel::GetVertexCount()
{
	return this->VertexCount;
}