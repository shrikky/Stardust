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

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(m_shaderID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string &name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(m_shaderID, name.c_str()), x, y);
}
// --
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(m_shaderID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(m_shaderID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(m_shaderID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(m_shaderID, name.c_str()), x, y, z, w);
}

//-----------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(m_shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(m_shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}