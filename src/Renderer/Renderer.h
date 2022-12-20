#pragma once

#include <map>
#include <cmath>

#include "DisplayManager.h"

#include "../Math/Matrix.h"
#include "../Math/Transform.h"
#include "../Entities/Entity.h"
#include "../Entities/Camera.h"
#include "../Shaders/StaticShader.h"

#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"

class Renderer
{
public:
	Renderer(StaticShader InShader);
	void Prepare();

	void Render(std::map<TexturedModel, Array<Entity>> InEntities);
	void Render(Entity InEntity, Camera InCamera);

private:
	void CreateProjectionMatrix();
	void PrepareTexturedModel(TexturedModel InModel);
	void UnbindTexturedModel();
	void PrepareInstance(Entity InEntity);

	StaticShader Shader;
	Matrix4<float> ProjectionMatrix;
	float FOV = 70.f;
	float NEAR_PLANE = .1f;
	float FAR_PLANE = 1000.f;
};