#include "Loader.h"

Loader::Loader()
{
	VAOs = Array<GLuint>();
	VBOs = Array<GLuint>();
	Textures = Array<GLuint>();
}

RawModel Loader::LoadToVAO(Array<float> InPositions, Array<float> InTextureCoords, Array<int> InIndices, Array<float> InNormals)
{
	GLuint VaoID;
	CreateVAO(VaoID);
	BindIndicesBuffer(InIndices);
	StoreDataInAttributeList(0, 3, InPositions);
	StoreDataInAttributeList(1, 2, InTextureCoords);
	StoreDataInAttributeList(2, 3, InNormals);
	UnbindVAO();
	return RawModel(VaoID, InIndices.Length());
}

GLuint Loader::LoadTexture(const char* InTexturePath)
{
	GLuint TextureID = SOIL_load_OGL_texture(InTexturePath, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	Textures.Add(TextureID);
	return TextureID;
}

void Loader::CreateVAO(GLuint& OutVaoId)
{
	glGenVertexArrays(1, &OutVaoId);
	glBindVertexArray(OutVaoId);
	VAOs.Add(OutVaoId);
}

void Loader::StoreDataInAttributeList(int InAttributeNumber, int InCoordinateSize, Array<float> InData)
{
	GLuint VboId;
	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, InData.Length() * sizeof(GLfloat), InData.GetData(), GL_STATIC_DRAW);
	glVertexAttribPointer(InAttributeNumber, InCoordinateSize, GL_FLOAT, false, 0, 0);
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

	Textures.ForEach([](GLuint TextureId) {
		glDeleteTextures(1, &TextureId);
	});
}
