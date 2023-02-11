/***************************************************************************************
Author: lvke
Date:2023/2/11 15:51
Description:
Shader
****************************************************************************************/
#pragma once
#include "Core/Basic/Macro.h"

namespace Enternity
{
	class Blob;
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
	private:
		unsigned int CompileShader(unsigned int shaderType, const char* shaderSourceCode);
		unsigned int CreateProgram(const char* vsShaderCode, const char* psShaderCode);
	private:
		unsigned int m_renderId;
	};
}