#include "Terrain.h"

float Terrain::SIZE = 800.f;
float Terrain::VERTEX_COUNT = 128.f;

Terrain::Terrain(int InGridX, int InGridZ, Loader InModelLoader, TerrainTexture InBlendMap, TerrainTexturePack InTexturePack)
	: BlendMap(InBlendMap)
	, TexturePack(InTexturePack)
	, X(InGridX * SIZE)
	, Z(InGridZ * SIZE)
	, Model(GenerateTerrain(InModelLoader))
{
}

RawModel Terrain::GenerateTerrain(Loader InModelLoader)
{
	int Count = VERTEX_COUNT * VERTEX_COUNT;
	Array<float> Vertices;
	Vertices.Assign(Count * 3, 0);

	Array<float> Normals;
	Normals.Assign(Count * 3, 0);

	Array<float> TextureCoords;
	TextureCoords.Assign(Count * 2, 0);

	Array<int> Indices;
	Indices.Assign(6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1), 0);

	int VertexPointer = 0;
	for (int i = 0; i < VERTEX_COUNT; i++)
	{
		for (int j = 0; j < VERTEX_COUNT; j++)
		{
			Vertices[VertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			Vertices[VertexPointer * 3 + 1] = 0;
			Vertices[VertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
			Normals[VertexPointer * 3] = 0;
			Normals[VertexPointer * 3 + 1] = 1;
			Normals[VertexPointer * 3 + 2] = 0;
			TextureCoords[VertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
			TextureCoords[VertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
			VertexPointer++;
		}
	}
	int Pointer = 0;
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++)
	{
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++)
		{
			int TopLeft = (gz * VERTEX_COUNT) + gx;
			int TopRight = TopLeft + 1;
			int BottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
			int BottomRight = BottomLeft + 1;
			Indices[Pointer++] = TopLeft;
			Indices[Pointer++] = BottomLeft;
			Indices[Pointer++] = TopRight;
			Indices[Pointer++] = TopRight;
			Indices[Pointer++] = BottomLeft;
			Indices[Pointer++] = BottomRight;
		}
	}
	return InModelLoader.LoadToVAO(Vertices, TextureCoords, Indices, Normals);
}