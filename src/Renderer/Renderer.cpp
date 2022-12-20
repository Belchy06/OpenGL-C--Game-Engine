#include "Renderer.h"

Renderer::Renderer(StaticShader InShader)
	: Shader(InShader)
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	CreateProjectionMatrix();
	Shader.Start();
	Shader.LoadProjectionMatrix(ProjectionMatrix);
	Shader.Stop();
}

void Renderer::Prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 0, 0, 1);
}

void Renderer::Render(std::map<TexturedModel, Array<Entity>> InEntities)
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

void Renderer::PrepareTexturedModel(TexturedModel InModel)
{
	RawModel RawModel = InModel.GetRawModel();

	glBindVertexArray(RawModel.GetVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	ModelTexture Texture = InModel.GetModelTexture();
	Shader.LoadShineVariables(Texture.GetShineDamper(), Texture.GetReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture.GetTextureID());
}

void Renderer::UnbindTexturedModel()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void Renderer::PrepareInstance(Entity InEntity)
{
	Transform<float> EntityTransformation(InEntity.GetPosition(), InEntity.GetScale(), InEntity.GetRotation());
	Shader.LoadTransformationMatrix(EntityTransformation.ToMatrix());
}

void Renderer::CreateProjectionMatrix()
{
	int Width, Height;
	glfwGetWindowSize(DisplayManager::Window, &Width, &Height);
	float AspectRatio = (float)Width / (float)Height;
	float YScale = (float)((1.f / tan(Math::ToRadians(FOV / 2.f))) * AspectRatio);
	float XScale = YScale / AspectRatio;
	float FrustumLength = FAR_PLANE - NEAR_PLANE;

	Array<float> Col0 = { XScale, 0, 0, 0 };
	Array<float> Col1 = { 0, YScale, 0, 0 };
	Array<float> Col2 = { 0, 0, -((FAR_PLANE + NEAR_PLANE) / FrustumLength), -1 };
	Array<float> Col3 = { 0, 0, -((2 * NEAR_PLANE * FAR_PLANE) / FrustumLength), 0 };
	ProjectionMatrix.SetAxes(Col0, Col1, Col2, Col3);
}