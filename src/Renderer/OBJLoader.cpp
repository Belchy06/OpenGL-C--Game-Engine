#include "OBJLoader.h"

RawModel OBJLoader::LoadObjModel(const char* InFilePath, Loader InModelLoader)
{
	std::ifstream File;
	File.open(InFilePath);

	Array<Vector3<float>> Vertices;
	Array<Vector2<float>> Textures;
	Array<Vector3<float>> Normals;
	Array<int> Indices;

	Array<float> VerticesArray;
	Array<float> NormalsArray;
	Array<float> TexturesArray;
	Array<int> IndicesArray;

	if (File.is_open())
	{
		std::string Line;
		while (std::getline(File, Line))
		{
			std::vector<std::string> Components = String::Split(Line, " ");
			if (Line[0] == 'v')
			{
				if (Line[1] == 't')
				{
					Vector2<float> Texture(std::stof(Components[1]), std::stof(Components[2]));
					Textures.Add(Texture);
				}
				else if (Line[1] == 'n')
				{
					Vector3<float> Normal(std::stof(Components[1]), std::stof(Components[2]), std::stof(Components[3]));
					Normals.Add(Normal);
				}
				else
				{
					Vector3<float> Vertex(std::stof(Components[1]), std::stof(Components[2]), std::stof(Components[3]));
					Vertices.Add(Vertex);
				}
			}
			else if (Line[0] == 'f')
			{
				TexturesArray.Assign(Vertices.Length() * 2, 0);
				NormalsArray.Assign(Vertices.Length() * 3, 0);
				break;
			}
		}

		while (std::getline(File, Line))
		{
			if (!(Line.at(0) == 'f'))
			{
				continue;
			}

			std::vector<std::string> Components = String::Split(Line, " ");
			std::vector<std::string> Vertex1 = String::Split(Components[1], "/");
			std::vector<std::string> Vertex2 = String::Split(Components[2], "/");
			std::vector<std::string> Vertex3 = String::Split(Components[3], "/");

			ProcessVertex(Vertex1, Indices, Textures, Normals, TexturesArray, NormalsArray);
			ProcessVertex(Vertex2, Indices, Textures, Normals, TexturesArray, NormalsArray);
			ProcessVertex(Vertex3, Indices, Textures, Normals, TexturesArray, NormalsArray);
		}
	}

	File.close();

	VerticesArray.Assign(Vertices.Length() * 3, 0);
	IndicesArray.Assign(Indices.Length(), 0);

	int VertexPointer = 0;
	Vertices.ForEach([&VertexPointer, &VerticesArray](Vector3<float> Vertex) {
		VerticesArray[VertexPointer++] = Vertex.X;
		VerticesArray[VertexPointer++] = Vertex.Y;
		VerticesArray[VertexPointer++] = Vertex.Z;
	});

	int i = 0;
	Indices.ForEach([&i, &IndicesArray, &Indices](Vector3<float> Index) {
		IndicesArray[i] = Indices[i];
		i++;
	});

	return InModelLoader.LoadToVAO(VerticesArray, TexturesArray, IndicesArray);
}

void OBJLoader::ProcessVertex(std::vector<std::string> InVertexData, Array<int>& InIndices, Array<Vector2<float>>& InTextures, Array<Vector3<float>>& InNormals, Array<float>& InTexturesArray, Array<float>& InNormalsArray)
{
	int CurrentVertexPointer = std::stoi(InVertexData[0]) - 1;
	InIndices.Add(CurrentVertexPointer);

	Vector2<float> CurrentTexture = InTextures[std::stoi(InVertexData[1]) - 1];
	InTexturesArray[CurrentVertexPointer * 2 + 0] = CurrentTexture.X;
	InTexturesArray[CurrentVertexPointer * 2 + 1] = CurrentTexture.Y;

	Vector3<float> CurrentNormal = InNormals[std::stoi(InVertexData[2]) - 1];
	InNormalsArray[CurrentVertexPointer * 3 + 0] = CurrentNormal.X;
	InNormalsArray[CurrentVertexPointer * 3 + 1] = CurrentNormal.Y;
	InNormalsArray[CurrentVertexPointer * 3 + 2] = CurrentNormal.Z;
}