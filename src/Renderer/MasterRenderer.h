#pragma once

#include <map>

#include "EntityRenderer.h"
#include "TerrainRenderer.h"

#include "../Math/Utility.h"
#include "../Containers/Array.h"
#include "../Terrain/Terrain.h"
#include "../Entities/Light.h"
#include "../Entities/Entity.h"
#include "../Entities/Camera.h"
#include "../Models/TexturedModel.h"
#include "../Shaders/StaticShader.h"
#include "../Shaders/TerrainShader.h"

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
	void Prepare();
	void Render(Light InSun, Camera InCamera);
	void ProcessEntity(Entity InEntity);
	void ProcessTerrain(Terrain InTerrain);

	static void SetCulling(bool bInEnabled);

private:
	Matrix4<float> CreateProjectionMatrix();

	StaticShader ShaderEntity;
	TerrainShader ShaderTerrain;

	EntityRenderer RendererEntity;
	TerrainRenderer RendererTerrain;

	std::map<TexturedModel, Array<Entity>> Entities;
	Array<Terrain> Terrains;

	static float FOV;
	static float NEAR_PLANE;
	static float FAR_PLANE;
};