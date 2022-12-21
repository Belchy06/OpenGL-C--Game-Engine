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

class EntityRenderer
{
public:
	EntityRenderer(StaticShader InShader, Matrix4<float> InProjectionMatrix);
	void Render(std::map<TexturedModel, Array<Entity>> InEntities);

private:
	void PrepareTexturedModel(TexturedModel InModel);
	void UnbindTexturedModel();
	void PrepareInstance(Entity InEntity);

	StaticShader Shader;
};