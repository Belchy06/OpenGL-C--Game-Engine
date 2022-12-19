
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <direct.h>
#define GLEW_STATIC
#include "../ThirdParty/glew-2.1.0/include/GL/glew.h"
#undef GLEW_STATIC
#include "../ThirdParty/glfw-3.3.8/include/GLFW/glfw3.h"

class ShaderProgram
{
public:
	ShaderProgram(const char* InVertexShaderPath, const char* InFragmentShaderPath);
	void Start();
	void Stop();
	void CleanUp();

private:
	GLuint LoadShader(const char* InShaderPath, int InShaderType);

	GLuint ProgramID;
	GLuint VertexShaderID;
	GLuint FragmentShaderID;

protected:
	virtual void BindAttributes() = 0;
	void BindAttribute(GLuint InAttribute, const char* InVariableName);
};