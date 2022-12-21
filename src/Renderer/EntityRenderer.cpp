#include "EntityRenderer.h"
#include "MasterRenderer.h"

EntityRenderer::EntityRenderer(StaticShader InShader, Matrix4<float> InProjectionMatrix)
	: Shader(InShader)
{
	Shader.Start();
	Shader.LoadProjectionMatrix(InProjectionMatrix);
	Shader.Stop();
}

void EntityRenderer::Render(std::map<TexturedModel, Array<Entity>> InEntities)
{
	for (std::map<TexturedModel, Array<Entity>>::iterator Iter = InEntities.begin(); Iter != InEntities.end(); ++Iter)
	{
		TexturedModel Model = Iter->first;

		PrepareTexturedModel(Model);
		Array<Entity> Batch = Iter->second;
		Batch.ForEach([this, &Model](Entity InEntity) {
			PrepareInstance(InEntity);
			glDrawElements(GL_TRIANGLES, Model.GetRawModel().GetVertexCount(), GL_UNSIGNED_INT, 0);
		});

		UnbindTexturedModel();
	}
}

void EntityRenderer::PrepareTexturedModel(TexturedModel InModel)
{
	RawModel RawModel = InModel.GetRawModel();

	glBindVertexArray(RawModel.GetVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	ModelTexture Texture = InModel.GetModelTexture();
	if (Texture.IsTransparent())
	{
		MasterRenderer::SetCulling(false);
	}
	Shader.LoadUseFakeLighting(Texture.IsUsingFakeLighting());
	Shader.LoadShineVariables(Texture.GetShineDamper(), Texture.GetReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture.GetTextureID());
}

void EntityRenderer::UnbindTexturedModel()
{
	MasterRenderer::SetCulling(true);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void EntityRenderer::PrepareInstance(Entity InEntity)
{
	Transform<float> EntityTransformation(InEntity.GetPosition(), InEntity.GetScale(), InEntity.GetRotation());
	Shader.LoadTransformationMatrix(EntityTransformation.ToMatrix());
}