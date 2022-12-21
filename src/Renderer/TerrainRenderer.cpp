#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer(TerrainShader InTerrainShader, Matrix4<float> InProjectionMatrix)
	: Shader(InTerrainShader)
	, ProjectionMatrix(InProjectionMatrix)
{
	Shader.Start();
	Shader.LoadProjectionMatrix(InProjectionMatrix);
	Shader.Stop();
}

void TerrainRenderer::Render(Array<Terrain> Terrains)
{
	Terrains.ForEach([this](Terrain InTerrain) {
		PrepareTerrain(InTerrain);
		LoadModelTransformation(InTerrain);
		glDrawElements(GL_TRIANGLES, InTerrain.GetModel().GetVertexCount(), GL_UNSIGNED_INT, 0);
		UnbindTerrain();
	});
}

void TerrainRenderer::PrepareTerrain(Terrain InTerrain)
{
	RawModel RawModel = InTerrain.GetModel();

	glBindVertexArray(RawModel.GetVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	ModelTexture Texture = InTerrain.GetTexture();
	Shader.LoadShineVariables(Texture.GetShineDamper(), Texture.GetReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture.GetTextureID());
}

void TerrainRenderer::UnbindTerrain()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void TerrainRenderer::LoadModelTransformation(Terrain InTerrain)
{
	Transform<float> EntityTransformation(Vector3<float>(InTerrain.GetX(), 0.0f, InTerrain.GetZ()), Vector3<float>::OneVector(), Quaternion<float>::Identity());
	Shader.LoadTransformationMatrix(EntityTransformation.ToMatrix());
}