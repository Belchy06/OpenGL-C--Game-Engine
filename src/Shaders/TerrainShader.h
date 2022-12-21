#pragma once

#include <map>
#include <string>

#include "ShaderProgram.h"

#include "../Entities/Light.h"

#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"

class TerrainShader : public ShaderProgram
{
public:
	TerrainShader();
	void LoadTransformationMatrix(Matrix4<float> InMatrix);
	void LoadProjectionMatrix(Matrix4<float> InMatrix);
	void LoadViewMatrix(Matrix4<float> InMatrix);
	void LoadLight(Light InLight);
	void LoadShineVariables(float Damper, float Reflectivity);
	void LoadSkyColour(Vector3<float> InColour);
	void ConnectTextureUnits();

	virtual void BindAttributes() override;
	virtual void GetAllUniformLocations() override;

private:
	static char* VERTEX_FILE;
	static char* FRAGMENT_FILE;

	std::map<std::string, GLuint> UniformLocations;
};