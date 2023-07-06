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

			m_vsShader = vsRendererAsset->getFullPath();
			m_psShader = psRendererAsset->getFullPath();
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

	void Renderer::setVec3(const std::string& name, const glm::vec3& vec3, bool normalize)
	{
		CHECK_GL_CALL(glUniform3fv(getUniformLocation(name), 1, &vec3[0]));
	}

	void Renderer::setUint1(const std::string& name, unsigned int value)
	{
		CHECK_GL_CALL(glUniform1uiv(getUniformLocation(name), 1, &value));
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

	void Enternity::Renderer::applyRenderPass()
	{
		glPolygonMode(GL_FRONT_AND_BACK, m_renderPass.fillMode + 0x1B00);
		m_renderPass.enableDepth ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
		if (m_renderPass.enableBlend)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else
		{
			glDisable(GL_BLEND);
		}
	}	
	
	void Enternity::Renderer::reCompile()
	{
		RendererAsset vsRendererAsset(m_vsShader);
		RendererAsset psRendererAsset(m_psShader);
		vsRendererAsset.load(0);
		psRendererAsset.load(0);

		if (vsRendererAsset.getLoadingState() == Asset::LoadingState::loading_state_succeeded &&
			psRendererAsset.getLoadingState() == Asset::LoadingState::loading_state_succeeded )
		{
			std::string vsStr((char*)vsRendererAsset.getBlob()->getData(), vsRendererAsset.getBlob()->getLength());
			std::string psStr((char*)psRendererAsset.getBlob()->getData(), psRendererAsset.getBlob()->getLength());
			
			unsigned int tmpRenderId = createProgram(vsStr.c_str(), psStr.c_str());
			if (tmpRenderId)
			{
				CHECK_GL_CALL(glDeleteProgram(m_renderId));
				m_renderId = tmpRenderId;
			}
		}			
	}
}