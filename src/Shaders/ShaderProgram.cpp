#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* InVertexShaderPath, const char* InFragmentShaderPath)
{
	VertexShaderID = LoadShader(InVertexShaderPath, GL_VERTEX_SHADER);
	FragmentShaderID = LoadShader(InFragmentShaderPath, GL_FRAGMENT_SHADER);

	// Link the program
	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
}

GLuint ShaderProgram::LoadShader(const char* InShaderPath, int InShaderType)
{
	// Read the Shader code from the file
	std::string ShaderCode;
	std::ifstream ShaderStream(InShaderPath, std::ios::in);
	if (ShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << ShaderStream.rdbuf();
		ShaderCode = sstr.str();
		ShaderStream.close();
	}
	else
	{
		char temp[256];
		if (_getcwd(temp, 256) != 0)
		{
			printf("%s", temp);
		}
		printf("Impossible to open %s. Are you in the right directory?\n", InShaderPath);
		return 0;
	}

	// Create the shaders
	GLuint ShaderID = glCreateShader(InShaderType);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Shader
	char const* ShaderSourcePointer = ShaderCode.c_str();
	glShaderSource(ShaderID, 1, &ShaderSourcePointer, NULL);
	glCompileShader(ShaderID);

	// Check Shader
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
		printf("%s\n", &ShaderErrorMessage[0]);
	}

	return ShaderID;
}

void ShaderProgram::Start()
{
	glUseProgram(ProgramID);
}

void ShaderProgram::Stop()
{
	glUseProgram(0);
}

void ShaderProgram::CleanUp()
{
	Stop();
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	glDeleteProgram(ProgramID);
}

void ShaderProgram::BindAttribute(GLuint InAttribute, const char* InVariableName)
{
	glBindAttribLocation(ProgramID, InAttribute, InVariableName);
}

GLuint ShaderProgram::GetUniformLocation(const char* InUniformName)
{
	return glGetUniformLocation(ProgramID, InUniformName);
}

void ShaderProgram::LoadFloat(GLuint InLocation, float InFloat)
{
	glUniform1f(InLocation, InFloat);
}

void ShaderProgram::LoadVector(GLuint InLocation, Vector3<float> InVector)
{
	glUniform3f(InLocation, InVector.X, InVector.Y, InVector.Z);
}

void ShaderProgram::LoadBool(GLuint InLocation, bool InBool)
{
	glUniform1f(InLocation, (InBool) ? 1.f : 0.f);
}

void ShaderProgram::LoadMatrix(GLuint InLocation, Matrix4<float> InMatrix)
{
	glUniformMatrix4fv(InLocation, 1, false, InMatrix.GetData());
}
