#include "Loader.h"

Loader::Loader()
{
	VAOs = Array<GLuint>();
	VBOs = Array<GLuint>();
}

RawModel Loader::LoadToVAO(Array<float> InPositions, Array<int> InIndices)
{
	GLuint VaoID;
	CreateVAO(VaoID);
	BindIndicesBuffer(InIndices);
	StoreDataInAttributeList(0, InPositions);
	UnbindVAO();
	return RawModel(VaoID, InIndices.Length());
}

void Loader::CreateVAO(GLuint& OutVaoId)
{
	glGenVertexArrays(1, &OutVaoId);
	glBindVertexArray(OutVaoId);
	VAOs.Add(OutVaoId);
}

void Loader::StoreDataInAttributeList(int InAttributeNumber, Array<float> InData)
{
	GLuint VboId;
	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, InData.Length() * sizeof(GLfloat), InData.GetData(), GL_STATIC_DRAW);
	glVertexAttribPointer(InAttributeNumber, 3, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	VBOs.Add(VboId);
}

void Loader::UnbindVAO()
{
	glBindVertexArray(0);
}

void Loader::BindIndicesBuffer(Array<int> InIndices)
{
	GLuint VboID;
	glGenBuffers(1, &VboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, InIndices.Length() * sizeof(int), InIndices.GetData(), GL_STATIC_DRAW);
	VBOs.Add(VboID);
}

void Loader::CleanUp()
{
	VAOs.ForEach([](GLuint VaoId) {
		glDeleteVertexArrays(1, &VaoId);
	});

	VBOs.ForEach([](GLuint VboId) {
		glDeleteBuffers(1, &VboId);
	});
}
