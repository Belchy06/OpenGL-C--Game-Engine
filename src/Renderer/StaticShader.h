#pragma once
#include "ShaderProgram.h"

class StaticShader : public ShaderProgram
{
public:
	StaticShader();

protected:
	virtual void BindAttributes() override;

private:
	static char* VERTEX_FILE;
	static char* FRAGMENT_FILE;
};