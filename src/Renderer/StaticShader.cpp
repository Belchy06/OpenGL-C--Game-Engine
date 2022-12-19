#include "StaticShader.h"

char* StaticShader::VERTEX_FILE = "./src/Shaders/VertexShader.txt";
char* StaticShader::FRAGMENT_FILE = "./src/Shaders/FragmentShader.txt";

StaticShader::StaticShader()
	: ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
}

void StaticShader::BindAttributes()
{
	BindAttribute(0, "position");
}
