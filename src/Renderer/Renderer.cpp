#include "Renderer.h"

Renderer::Renderer(StaticShader InShader)
	: Shader(InShader)
{
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

void Renderer::Render(Entity InEntity, Camera InCamera)
{
	TexturedModel Model = InEntity.GetModel();
	RawModel RawModel = Model.GetRawModel();

	glBindVertexArray(RawModel.GetVaoId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	Shader.LoadTransformationMatrix(Transform<float>(InEntity.GetPosition(), InEntity.GetScale(), InEntity.GetRotation()).ToMatrix());

	Vector3<float> CameraPosition = InCamera.GetPosition() * -1;
	Vector3<float> CameraScale = Vector3<float>::OneVector();
	Rotator<float> CameraRotation = InCamera.GetRotation();
	Transform<float> ViewTransform(CameraPosition, CameraScale, CameraRotation);

	Shader.LoadViewMatrix(ViewTransform.ToMatrix());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Model.GetModelTexture().GetTextureID());
	glDrawElements(GL_TRIANGLES, RawModel.GetVertexCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
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