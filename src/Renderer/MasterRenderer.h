#pragma once

#include <map>

#include "Renderer.h"

#include "../Math/Array.h"
#include "../Entities/Light.h"
#include "../Entities/Entity.h"
#include "../Entities/Camera.h"
#include "../Models/TexturedModel.h"
#include "../Shaders/StaticShader.h"

namespace std
{
	template <>
	struct less<TexturedModel>
	{
		bool operator()(const TexturedModel& LHS, const TexturedModel& RHS) const
		{
			return LHS.GetModelTexture().GetTextureID() < RHS.GetModelTexture().GetTextureID();
		}
	};
} // namespace std

class MasterRenderer
{
public:
	MasterRenderer();
	void CleanUp();
	void Render(Light InSun, Camera InCamera);
	void ProcessEntity(Entity InEntity);

private:
	StaticShader Shader;
	Renderer SceneRender;

	std::map<TexturedModel, Array<Entity>> Entities;
};