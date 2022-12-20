#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <direct.h>

#include "../Math/Array.h"
#include "../Math/Matrix.h"
#include "../Math/Vector.h"

#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"
#include "../ThirdParty/glfw-3.3.8/include/GLFW/glfw3.h"

class ShaderProgram
{
public:
	ShaderProgram(const char* InVertexShaderPath, const char* InFragmentShaderPath);
	void Start();
	void Stop();
	void CleanUp();

protected:
	virtual void BindAttributes() = 0;
	virtual void GetAllUniformLocations() = 0;
	void BindAttribute(GLuint InAttribute, const char* InVariableName);
	GLuint GetUniformLocation(const char* InUniformName);
	void LoadFloat(GLuint InLocation, float InFloat);
	void LoadVector(GLuint InLocation, Vector3<float> InVector);
	void LoadBool(GLuint InLocation, bool InBool);
	void LoadMatrix(GLuint InLocation, Matrix4<float> InMatrix);

private:
	GLuint LoadShader(const char* InShaderPath, int InShaderType);

	GLuint ProgramID;
	GLuint VertexShaderID;
	GLuint FragmentShaderID;
};