#include "MasterRenderer.h"

float MasterRenderer::FOV = 70.f;
float MasterRenderer::NEAR_PLANE = .1f;
float MasterRenderer::FAR_PLANE = 1000.f;
Vector3<float> MasterRenderer::SKY_COLOUR = Vector3<float>(0.529, 0.808, 0.929);

MasterRenderer::MasterRenderer()
	: ShaderEntity()
	, ShaderTerrain()
	, RendererEntity(ShaderEntity, CreateProjectionMatrix())
	, RendererTerrain(ShaderTerrain, CreateProjectionMatrix())
{
	SetCulling(true);
}

void MasterRenderer::CleanUp()
{
	ShaderEntity.CleanUp();
}

void MasterRenderer::Render(Light InSun, Camera InCamera)
{
	Prepare();
	ShaderEntity.Start();
	ShaderEntity.LoadSkyColour(SKY_COLOUR);
	ShaderEntity.LoadLight(InSun);
	ShaderEntity.LoadViewMatrix(InCamera.GetTransformationMatrix());
	RendererEntity.Render(Entities);
	ShaderEntity.Stop();
	Entities.clear();

	ShaderTerrain.Start();
	ShaderTerrain.LoadSkyColour(SKY_COLOUR);
	ShaderTerrain.LoadLight(InSun);
	ShaderTerrain.LoadViewMatrix(InCamera.GetTransformationMatrix());
	RendererTerrain.Render(Terrains);
	ShaderTerrain.Stop();
	Terrains.Clear();
}

void MasterRenderer::ProcessEntity(Entity* InEntity)
{
	TexturedModel EntityModel = InEntity->GetModel();
	Array<Entity*> Batch = Entities[EntityModel];
	Batch.Add(InEntity);
	Entities[EntityModel] = Batch;
}

void MasterRenderer::ProcessTerrain(Terrain InTerrain)
{
	Terrains.Add(InTerrain);
}

void MasterRenderer::SetCulling(bool bInEnabled)
{
	if (bInEnabled)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}
}

void MasterRenderer::SetWireframe(bool bInEnabled)
{
	if (bInEnabled)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

Matrix4<float> MasterRenderer::CreateProjectionMatrix()
{
	int Width, Height;
	glfwGetWindowSize(DisplayManager::Window, &Width, &Height);
	float AspectRatio = (float)Width / (float)Height;
	float YScale = (float)((1.f / tan(Math::ToRadians(FOV / 2.f))) * AspectRatio);
	float XScale = YScale / AspectRatio;
	float FrustumLength = FAR_PLANE - NEAR_PLANE;

	Matrix4<float> Matrix;
	Array<float> Col0 = { XScale, 0, 0, 0 };
	Array<float> Col1 = { 0, YScale, 0, 0 };
	Array<float> Col2 = { 0, 0, -((FAR_PLANE + NEAR_PLANE) / FrustumLength), -1 };
	Array<float> Col3 = { 0, 0, -((2 * NEAR_PLANE * FAR_PLANE) / FrustumLength), 0 };
	Matrix.SetAxes(Col0, Col1, Col2, Col3);
	return Matrix;
}

void MasterRenderer::Prepare()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(SKY_COLOUR.X, SKY_COLOUR.Y, SKY_COLOUR.Z, 1);
}