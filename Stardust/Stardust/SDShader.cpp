#include "SDShader.h"


Shader::Shader() 
{
	m_shaderID = glCreateProgram();
}

void Shader::Use()
{
	glUseProgram(m_shaderID);
}

void Shader::SetBool(const std::string & name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string & name, int value) const
{
	glUniform1i(glGetUniformLocation(m_shaderID, name.c_str()), value);
}

void Shader::SetFloat(const std::string & name, float value) const
{
	glUniform1f(glGetUniformLocation(m_shaderID, name.c_str()), value);
}

void Shader::CompileShader(const std::string & path, ShaderType  type)
{
	std::string shaderCode;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {

		shaderFile.open(path);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		shaderCode = shaderStream.str();
	}

	catch(std::ifstream::failure e)
	{
		std::cout << "Error: " << std::to_string((ShaderType)type) << " File_NOT_READ" << std::endl;
	}

	const char* cShaderCode = shaderCode.c_str();
	unsigned int coreShaderType;
	int success;
	int shaderType = 0;

	switch (type)
	{
	case Shader::VERTEX:
		shaderType = GL_VERTEX_SHADER;
		break;
	case Shader::FRAGMENT:
		shaderType = GL_FRAGMENT_SHADER;
		break;
	case Shader::GEOMETRY:
		shaderType = GL_GEOMETRY_SHADER;
		break;
	case Shader::COMPUTE:
		shaderType = GL_COMPUTE_SHADER;
		break;
	default:
		break;
	}

	// Compile Shader
	coreShaderType = glCreateShader(shaderType);
	glShaderSource(coreShaderType, 1, &cShaderCode, NULL);
	glCompileShader(coreShaderType);

	// Link Shader
	glAttachShader(m_shaderID, coreShaderType);
	glLinkProgram(m_shaderID);
	glGetProgramiv(m_shaderID, GL_LINK_STATUS, &success);

	//Clean Up
	CompileShader(coreShaderType, std::to_string(shaderType));
	glDeleteShader(coreShaderType);

}

void Shader::CompileShader(unsigned int shader, std::string type)
{

	int success;
	char infoLog[1024];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	if (!success)
	{
		glGetProgramInfoLog(m_shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}


int Shader::GetShaderProgramID()
{
	return m_shaderID;
}