/***************************************************************************************
Author: lvke
Date:2022/12/31 20:29
Description:
Encapsulate  Shader
****************************************************************************************/
#pragma once

#include "Interface/BindableInterface.h"
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

BEGIN_ENTERNITY

struct ShaderSourceCode
{
	std::string VertexShaderSourceCode;
	std::string PixelShaderSourceCode;
};

class Shader : public IBindable
{
public:
	Shader() = default;
	Shader(const std::string& filePath);
	virtual ~Shader();

	virtual void Bind(unsigned int slot = 0) const override;
	virtual void UnBind() const override;

	
	void SetInteger1(const std::string& name, int value);
	void SetFloat3(const std::string& name, float v0, float v1, float v2);
	void SetFloat3(const std::string& name, const glm::vec3& v3);
	void SetFloat4(const std::string& name, float v0, float v1, float v2, float v3);
	void SetFloat4(const std::string& name, const glm::vec4& v4);
	void SetMat4f(const std::string& name, const glm::mat4& mat4, bool normalize = false);
private:
	bool ParseShaderFile(ShaderSourceCode& shaderSourceCode, const std::string& filePath);
	unsigned int CompileShader(unsigned int shaderType, const char* shaderSourceCode);
	unsigned int CreateProgram(const std::string& vsShaderCode, const std::string& psShaderCode);

	int GetUniformLocation(const std::string& name);
	std::unordered_map<std::string, int> m_uniformLocationCache;
};

END_ENTERNITY
