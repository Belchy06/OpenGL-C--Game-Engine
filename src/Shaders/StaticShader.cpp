#include "StaticShader.h"

char* StaticShader::VERTEX_FILE = "./src/Shaders/VertexShader.txt";
char* StaticShader::FRAGMENT_FILE = "./src/Shaders/FragmentShader.txt";

StaticShader::StaticShader()
	: ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
	GetAllUniformLocations();
}

void StaticShader::BindAttributes()
{
	BindAttribute(0, "position");
	BindAttribute(1, "textureCoords");
	BindAttribute(2, "normal");
}

void StaticShader::LoadTransformationMatrix(Matrix4<float> InMatrix)
{
	LoadMatrix(UniformLocations["transformationMatrix"], InMatrix);
}

void StaticShader::LoadProjectionMatrix(Matrix4<float> InMatrix)
{
	LoadMatrix(UniformLocations["projectionMatrix"], InMatrix);
}

void StaticShader::LoadViewMatrix(Matrix4<float> InMatrix)
{
	LoadMatrix(UniformLocations["viewMatrix"], InMatrix);
}

void StaticShader::LoadLight(Light InLight)
{
	LoadVector(UniformLocations["lightPosition"], InLight.GetPosition());
	LoadVector(UniformLocations["lightColour"], InLight.GetColour());
}

void StaticShader::LoadShineVariables(float Damper, float Reflectivity)
{
	LoadFloat(UniformLocations["shineDamper"], Damper);
	LoadFloat(UniformLocations["reflectivity"], Reflectivity);
}

void StaticShader::LoadUseFakeLighting(bool bUseFakeLighting)
{
	LoadBool(UniformLocations["useFakeLighting"], bUseFakeLighting);
}

void StaticShader::GetAllUniformLocations()
{
	UniformLocations["transformationMatrix"] = GetUniformLocation("transformationMatrix");
	UniformLocations["projectionMatrix"] = GetUniformLocation("projectionMatrix");
	UniformLocations["viewMatrix"] = GetUniformLocation("viewMatrix");
	UniformLocations["lightPosition"] = GetUniformLocation("lightPosition");
	UniformLocations["lightColour"] = GetUniformLocation("lightColour");
	UniformLocations["shineDamper"] = GetUniformLocation("shineDamper");
	UniformLocations["reflectivity"] = GetUniformLocation("reflectivity");
	UniformLocations["useFakeLighting"] = GetUniformLocation("useFakeLighting");
}
