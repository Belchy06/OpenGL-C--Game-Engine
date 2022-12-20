#include "MasterRenderer.h"

MasterRenderer::MasterRenderer()
	: Shader()
	, SceneRender(Shader)
{
}

void MasterRenderer::CleanUp()
{
	Shader.CleanUp();
}

void MasterRenderer::Render(Light InSun, Camera InCamera)
{
	SceneRender.Prepare();
	Shader.Start();
	Shader.LoadLight(InSun);
	Shader.LoadViewMatrix(InCamera.GetTransformationMatrix());
	SceneRender.Render(Entities);
	Shader.Stop();
	Entities.clear();
}

void MasterRenderer::ProcessEntity(Entity InEntity)
{
	TexturedModel EntityModel = InEntity.GetModel();
	Array<Entity> Batch = Entities[EntityModel];
	Batch.Add(InEntity);
	Entities[EntityModel] = Batch;
}