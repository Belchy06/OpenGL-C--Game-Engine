#pragma once

#include "../Containers/Array.h"
#include "../Math/Matrix.h"
#include "../Models/TexturedModel.h"
#include "../Terrain/Terrain.h"
#include "../Shaders/TerrainShader.h"

#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"

class TerrainRenderer
{
public:
	TerrainRenderer(TerrainShader InTerrainShader, Matrix4<float> InProjectionMatrix);
	void Render(Array<Terrain> Terrains);

private:
	void PrepareTerrain(Terrain InTerrain);
	void UnbindTerrain();
	void LoadModelTransformation(Terrain InTerrain);
	void BindTextures(Terrain InTerrain);

	TerrainShader Shader;
	Matrix4<float> ProjectionMatrix;
};