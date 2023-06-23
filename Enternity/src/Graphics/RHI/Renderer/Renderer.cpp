#include "Renderer.h"
#include "RendererAsset.h"
#include "Engine/Blob.h"
#include "Common/Macro.h"
#include "Engine/Log.h"
#include <glad/glad.h>

namespace Enternity
{
	Renderer::Renderer(RendererAsset* vsRendererAsset, RendererAsset* psRendererAsset, RendererAsset* gsRendererAsset)
	{
		if (vsRendererAsset && vsRendererAsset->getBlob() && psRendererAsset && vsRendererAsset->getBlob())
		{
			std::string vsStr((char*)vsRendererAsset->getBlob()->getData(), vsRendererAsset->getBlob()->getLength());
			std::string psStr((char*)psRendererAsset->getBlob()->getData(), psRendererAsset->getBlob()->getLength());
			m_renderId = createProgram(vsStr.c_str(), psStr.c_str());
		}
	}

	Renderer::~Renderer()
	{
		CHECK_GL_CALL(glDeleteProgram(m_renderId));
	}

	void Renderer::bind()
	{
		CHECK_GL_CALL(glUseProgram(m_renderId));
	}

	void Renderer::unbind()
	{
		CHECK_GL_CALL(glUseProgram(0));
	}

	unsigned int Renderer::createProgram(const char* vsShaderCode, const char* psShaderCode)
	{
		CHECK_GL_CALL(unsigned int program = glCreateProgram());

		unsigned int vsShader = compileShader(GL_VERTEX_SHADER, vsShaderCode);
		unsigned int psShader = compileShader(GL_FRAGMENT_SHADER, psShaderCode);

		CHECK_GL_CALL(glAttachShader(program, vsShader));
		CHECK_GL_CALL(glAttachShader(program, psShader));
		CHECK_GL_CALL(glLinkProgram(program));
		CHECK_GL_CALL(glValidateProgram(program));

		int result;
		CHECK_GL_CALL(glGetProgramiv(program, GL_LINK_STATUS, &result));
		if (result == GL_FALSE)
		{
			int infoLength;
			CHECK_GL_CALL(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength));

			char* errorInfo = new char[infoLength];
			CHECK_GL_CALL(glGetProgramInfoLog(program, infoLength, &infoLength, errorInfo));
			LOG_ERROR(errorInfo);
			//printf("%s\n", errorInfo);
			delete[] errorInfo;

			CHECK_GL_CALL(glDeleteProgram(program));

			return 0;
		}

		CHECK_GL_CALL(glDeleteShader(vsShader));
		CHECK_GL_CALL(glDeleteShader(psShader));

		return program;
	}

	unsigned int Renderer::compileShader(unsigned int shaderType, const char* shaderSourceCode)
	{
		unsigned int shader;
		CHECK_GL_CALL(shader = glCreateShader(shaderType));
		CHECK_GL_CALL(glShaderSource(shader, 1, &shaderSourceCode, nullptr));
		CHECK_GL_CALL(glCompileShader(shader));

		int result;
		CHECK_GL_CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE)
		{
			int infoLength;
			CHECK_GL_CALL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength));

			char* errorInfo = new char[infoLength];
			CHECK_GL_CALL(glGetShaderInfoLog(shader, infoLength, &infoLength, errorInfo));
			LOG_ERROR(errorInfo);
			//printf("%s\n", errorInfo);
			delete[] errorInfo;

			CHECK_GL_CALL(glDeleteShader(shader));
			return 0;
		}

		return shader;
	}

	void Renderer::setMat4(const std::string & name, const glm::mat4 & mat4, bool normalize)
	{
		CHECK_GL_CALL(glUniformMatrix4fv(getUniformLocation(name), 1, normalize, &mat4[0][0]));
	}

	int Renderer::getUniformLocation(const std::string& name)
	{
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
			return m_uniformLocationCache[name];

		int location;
		CHECK_GL_CALL(location = glGetUniformLocation(m_renderId, name.c_str()));
		m_uniformLocationCache[name] = location;
		if (location == -1)
		{
			LOG_ERROR("uniform: " + name + " doesn't exist (or never use)");
		}
		return location;
	}
}