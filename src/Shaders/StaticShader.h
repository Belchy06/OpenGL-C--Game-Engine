#pragma once

#include <map>
#include <string>

#include "ShaderProgram.h"

#include "../Entities/Light.h"

#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
	void LoadTransformationMatrix(Matrix4<float> InMatrix);
	void LoadProjectionMatrix(Matrix4<float> InMatrix);
	void LoadViewMatrix(Matrix4<float> InMatrix);
	void LoadLight(Light InLight);
	void LoadShineVariables(float Damper, float Reflectivity);
	void LoadUseFakeLighting(bool bUseFakeLighting);
	void LoadSkyColour(Vector3<float> InColour);

	virtual void BindAttributes() override;
	virtual void GetAllUniformLocations() override;

private:
	static char* VERTEX_FILE;
	static char* FRAGMENT_FILE;

	std::map<std::string, GLuint> UniformLocations;
};