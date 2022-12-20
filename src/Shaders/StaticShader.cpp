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

void StaticShader::GetAllUniformLocations()
{
	UniformLocations["transformationMatrix"] = GetUniformLocation("transformationMatrix");
	UniformLocations["projectionMatrix"] = GetUniformLocation("projectionMatrix");
	UniformLocations["viewMatrix"] = GetUniformLocation("viewMatrix");
}
