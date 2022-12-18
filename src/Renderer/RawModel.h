#pragma once

class RawModel
{
public:
	RawModel(unsigned int InVaoId, int InVertexCount);
	unsigned int GetVaoId();
	int GetVertexCount();

private:
	unsigned int VaoID;
	int VertexCount;
};