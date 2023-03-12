/***************************************************************************************
Author: lvke
Date:2023/2/11 15:51
Description:
Shader
****************************************************************************************/
#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace Enternity
{
	class Blob;
	class Shader
	{
	public:
		~Shader();

	public:
		void init(Blob* vsBlob, Blob* psBlob);
		void bind();
		void unbind();
	public:
		void setMat4(const std::string& name, const glm::mat4& mat4, bool transpose);
	private:
		unsigned int CompileShader(unsigned int shaderType, const char* shaderSourceCode);
		unsigned int CreateProgram(const char* vsShaderCode, const char* psShaderCode);

		int getUniformLocation(const std::string& name);
		std::unordered_map<std::string, int> m_uniformLocationCache;
	private:
		unsigned int m_renderId;
	};
}