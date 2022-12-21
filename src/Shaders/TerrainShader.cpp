#include "TerrainShader.h"

char* TerrainShader::VERTEX_FILE = "./src/Shaders/TerrainVertexShader.txt";
char* TerrainShader::FRAGMENT_FILE = "./src/Shaders/TerrainFragmentShader.txt";

TerrainShader::TerrainShader()
	: ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
	GetAllUniformLocations();
}

void TerrainShader::BindAttributes()
{
	BindAttribute(0, "position");
	BindAttribute(1, "textureCoords");
	BindAttribute(2, "normal");
}

void TerrainShader::LoadTransformationMatrix(Matrix4<float> InMatrix)
{
	LoadMatrix(UniformLocations["transformationMatrix"], InMatrix);
}

void TerrainShader::LoadProjectionMatrix(Matrix4<float> InMatrix)
{
	LoadMatrix(UniformLocations["projectionMatrix"], InMatrix);
}

void TerrainShader::LoadViewMatrix(Matrix4<float> InMatrix)
{
	LoadMatrix(UniformLocations["viewMatrix"], InMatrix);
}

void TerrainShader::LoadLight(Light InLight)
{
	LoadVector(UniformLocations["lightPosition"], InLight.GetPosition());
	LoadVector(UniformLocations["lightColour"], InLight.GetColour());
}

void TerrainShader::LoadShineVariables(float Damper, float Reflectivity)
{
	LoadFloat(UniformLocations["shineDamper"], Damper);
	LoadFloat(UniformLocations["reflectivity"], Reflectivity);
}

void TerrainShader::GetAllUniformLocations()
{
	UniformLocations["transformationMatrix"] = GetUniformLocation("transformationMatrix");
	UniformLocations["projectionMatrix"] = GetUniformLocation("projectionMatrix");
	UniformLocations["viewMatrix"] = GetUniformLocation("viewMatrix");
	UniformLocations["lightPosition"] = GetUniformLocation("lightPosition");
	UniformLocations["lightColour"] = GetUniformLocation("lightColour");
	UniformLocations["shineDamper"] = GetUniformLocation("shineDamper");
	UniformLocations["reflectivity"] = GetUniformLocation("reflectivity");
}