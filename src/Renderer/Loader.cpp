#include "Loader.h"

Loader::Loader()
{
	VAOs = Array<GLuint>();
	VBOs = Array<GLuint>();
}

RawModel Loader::LoadToVAO(Array<float> InPositions)
{
	GLuint VaoID;
	CreateVAO(VaoID);
	GLuint VboID;
	StoreDataInAttributeList(0, InPositions, VboID);
	UnbindVAO();
	return RawModel(VaoID, InPositions.Length() / 3);
}

void Loader::CreateVAO(GLuint& OutVaoId)
{
	glGenVertexArrays(1, &OutVaoId);
	glBindVertexArray(OutVaoId);
	VAOs.Add(OutVaoId);
}

void Loader::StoreDataInAttributeList(int InAttributeNumber, Array<float> InData, GLuint& OutVboId)
{
	glGenBuffers(1, &OutVboId);
	glBindBuffer(GL_ARRAY_BUFFER, OutVboId);
	glBufferData(GL_ARRAY_BUFFER, InData.Length() * sizeof(GLfloat), InData.GetData(), GL_STATIC_DRAW);
	glVertexAttribPointer(InAttributeNumber, 3, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	VBOs.Add(OutVboId);
}

void Loader::UnbindVAO()
{
	glBindVertexArray(0);
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
