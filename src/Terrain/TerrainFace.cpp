#include "TerrainFace.h"

float TerrainFace::SIZE = 20.f;
float TerrainFace::VERTEX_COUNT = 32.f;

TerrainFace::TerrainFace(int InGridX, int InGridZ, Loader InModelLoader, TerrainTexture InBlendMap, TerrainTexturePack InTexturePack, Vector3<float> InLocalUp)
	: Terrain(InGridX, InGridZ, InModelLoader, InBlendMap, InTexturePack)
	, LocalUp(InLocalUp)
{
	AxisA = Vector3<float>(LocalUp.Y, LocalUp.Z, LocalUp.X);
	AxisB = LocalUp.Cross(AxisA);

	Model = GenerateTerrain(InModelLoader);
}

RawModel TerrainFace::GenerateTerrain(Loader InModelLoader)
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
			Vector2<float> Percent = Vector2<float>(j / (VERTEX_COUNT - 1), i / (VERTEX_COUNT - 1));
			Vector3<float> TempA = AxisA * 2.f * (Percent.X - .5f);
			Vector3<float> TempB = AxisB * 2.f * (Percent.Y - .5f);
			Vector3<float> PointOnUnitCube = LocalUp + TempA + TempB;
			Vector3<float> PointOnUnitSphere = PointOnUnitCube.Normalize();

			Vertices[VertexPointer * 3] = PointOnUnitSphere.X * SIZE;
			Vertices[VertexPointer * 3 + 1] = PointOnUnitSphere.Y * SIZE;
			Vertices[VertexPointer * 3 + 2] = PointOnUnitSphere.Z * SIZE;
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