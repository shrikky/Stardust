#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader
{
public:
	enum ShaderType
	{
		VERTEX,
		FRAGMENT,
		GEOMETRY,
		COMPUTE
	};
	Shader();
	ShaderType m_shaderType;
	unsigned int m_shaderID;
	int GetShaderProgramID();
	void Use();
	void SetBool(const std::string &name, bool value) const; 
	void SetInt(const std::string &name, int value) const; ;
	void SetFloat(const std::string &name, float value) const;
	void CompileShader(const std::string &name, ShaderType type);
	void CompileShader(unsigned int shader, std::string type);
	void setVec2(const std::string &name, const glm::vec2 &value) const;
	void setVec2(const std::string &name, float x, float y) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec4(const std::string &name, const glm::vec4 &value) const;
	void setVec4(const std::string &name, float x, float y, float z, float w) const;
	void setMat2(const std::string &name, const glm::mat2 &mat) const;
	void setMat3(const std::string &name, const glm::mat3 &mat) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;


};
#endif
