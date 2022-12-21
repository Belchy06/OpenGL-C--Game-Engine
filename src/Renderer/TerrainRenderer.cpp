#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer(TerrainShader InTerrainShader, Matrix4<float> InProjectionMatrix)
	: Shader(InTerrainShader)
	, ProjectionMatrix(InProjectionMatrix)
{
	Shader.Start();
	Shader.LoadProjectionMatrix(InProjectionMatrix);
	Shader.ConnectTextureUnits();
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

	BindTextures(InTerrain);
	Shader.LoadShineVariables(1, 0);
}

void TerrainRenderer::BindTextures(Terrain InTerrain)
{
	TerrainTexturePack TexturePack = InTerrain.GetTexturePack();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexturePack.GetBackgroundTexture().GetTextureID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TexturePack.GetRTexture().GetTextureID());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, TexturePack.GetGTexture().GetTextureID());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, TexturePack.GetBTexture().GetTextureID());
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, InTerrain.GetBlendMap().GetTextureID());
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