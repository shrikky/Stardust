#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

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
};
#endif
