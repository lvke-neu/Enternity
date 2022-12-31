/***************************************************************************************
Author: lvke
Date:2022/12/31 20:29
Description:
Encapsulate  Shader
****************************************************************************************/
#pragma once

#include "Interface/RendererInterface.h"
#include <string>
#include <unordered_map>

BEGIN_ENTERNITY

struct ShaderSourceCode
{
	std::string VertexShaderSourceCode;
	std::string PixelShaderSourceCode;
};

class Shader : public IRenderer
{
public:
	Shader(const std::string& filePath);
	virtual ~Shader();

	virtual void Bind() const override;
	virtual void UnBind() const override;

	void setFloat4(const std::string& name, float v0, float v1, float v2, float v3);
private:
	ShaderSourceCode ParseShaderFile(const std::string& filePath);
	unsigned int CompileShader(unsigned int shaderType, const char* shaderSourceCode);
	unsigned int CreateProgram(const std::string& vsShaderCode, const std::string& psShaderCode);

	std::unordered_map<std::string, int> m_uniformLocationCache;
};

END_ENTERNITY
