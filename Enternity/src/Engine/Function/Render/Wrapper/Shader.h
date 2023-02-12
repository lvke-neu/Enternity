/***************************************************************************************
Author: lvke
Date:2023/2/11 15:51
Description:
Shader
****************************************************************************************/
#pragma once
#include "Core/Basic/Macro.h"
#include <string>
#include <unordered_map>

namespace Enternity
{
	class Blob;
	class Matrix4x4f;
	class Shader
	{
		friend class RenderWrapper;
		PRIVATE(Shader);
	private:
		void Destroy();

	public:
		void init(Blob* vsBlob, Blob* psBlob);
		void bind();
		void unbind();
	public:
		void setMat4(const std::string& name, const Matrix4x4f& mat4, bool transpose);
	private:
		unsigned int CompileShader(unsigned int shaderType, const char* shaderSourceCode);
		unsigned int CreateProgram(const char* vsShaderCode, const char* psShaderCode);

		int getUniformLocation(const std::string& name);
		std::unordered_map<std::string, int> m_uniformLocationCache;
	private:
		unsigned int m_renderId;
	};
}