#include "Renderer.h"
#include "RendererBlobHolder.h"
#include "Engine/Blob.h"
#include "Engine/Log.h"
#include <glad/glad.h>

namespace Enternity
{
	Renderer::~Renderer()
	{
		glDeleteProgram(m_renderId);
	}

	void Renderer::load(BlobHolder* blobHolder)
	{
		RendererBlobHolder* rendererBlobHolder = dynamic_cast<RendererBlobHolder*>(blobHolder);
		if (!rendererBlobHolder || !rendererBlobHolder->isLoadSucceeded() || !rendererBlobHolder->getBlob())
		{
			m_state = loading_state_failed;
			return;
		}

		std::string vertShaderCode;
		std::string geomShaderCode;
		std::string fragShaderCode;

		for (auto type : rendererBlobHolder->m_shaderTypes)
		{
			bool bShaderCorrent = false;
			
			if (type == RendererBlobHolder::VertexShader)
			{
				vertShaderCode = std::string((char*)rendererBlobHolder->getBlob()->getData() + rendererBlobHolder->m_shaderDesc.vertDataOffset,
					rendererBlobHolder->m_shaderDesc.vertDataSize);
			}

			if (type == RendererBlobHolder::GeometryShader)
			{
				geomShaderCode = std::string((char*)rendererBlobHolder->getBlob()->getData() + rendererBlobHolder->m_shaderDesc.geomDataOffset,
					rendererBlobHolder->m_shaderDesc.geomDataSize);
			}

			if (type == RendererBlobHolder::FragmentShader)
			{
				fragShaderCode = std::string((char*)rendererBlobHolder->getBlob()->getData() + rendererBlobHolder->m_shaderDesc.fragDataOffset,
					rendererBlobHolder->m_shaderDesc.fragDataSize);
			}
		}

		unsigned int vertShaderRenderId;
		unsigned int fragShaderRenderId;

		unsigned int geomShaderRenderId;
		bool bCompileGeomShader = false;

		if (!compileShader(vertShaderRenderId, GL_VERTEX_SHADER, vertShaderCode.c_str(), blobHolder->getPath()))
		{
			m_state = loading_state_failed;
			return;
		}

		if (!compileShader(fragShaderRenderId, GL_FRAGMENT_SHADER, fragShaderCode.c_str(), blobHolder->getPath()))
		{
			m_state = loading_state_failed;
			return;
		}

		m_renderId = glCreateProgram();
		
		glAttachShader(m_renderId, vertShaderRenderId);
		glAttachShader(m_renderId, fragShaderRenderId);
		if (geomShaderCode != "")
		{
			compileShader(geomShaderRenderId, GL_GEOMETRY_SHADER, geomShaderCode.c_str(), blobHolder->getPath());
			bCompileGeomShader = true;
			glAttachShader(m_renderId, geomShaderRenderId);
		}
		
		glLinkProgram(m_renderId);
		glValidateProgram(m_renderId);
		int result;
		glGetProgramiv(m_renderId, GL_LINK_STATUS, &result);
		if (result == GL_FALSE)
		{
			int infoLength;
			glGetProgramiv(m_renderId, GL_INFO_LOG_LENGTH, &infoLength);

			char* errorInfo = new char[infoLength];
			glGetProgramInfoLog(m_renderId, infoLength, &infoLength, errorInfo);
			LOG_ERROR("{0} Link Shader Failed:{1}", blobHolder->getPath(), errorInfo);
			//printf("%s\n", errorInfo);
			delete[] errorInfo;

			glDeleteProgram(m_renderId);

			m_state = loading_state_failed;
			return;
		}

		glDeleteShader(vertShaderRenderId);
		glDeleteShader(fragShaderRenderId);
		if (bCompileGeomShader)
		{
			glDeleteShader(geomShaderRenderId);
		}

		m_state = loading_state_succeeded;
	}

	void Renderer::unload()
	{
		glDeleteProgram(m_renderId);
		m_state = loading_state_pending;
	}

	void Renderer::bind()
	{
		glUseProgram(m_renderId);
	}

	void Renderer::unbind()
	{
		glUseProgram(0);
	}

	void Renderer::setInt1(const std::string& name, int value)
	{
		glUniform1iv(getUniformLocation(name), 1, &value);
	}

	void Renderer::setUint1(const std::string& name, unsigned int value)
	{
		glUniform1uiv(getUniformLocation(name), 1, &value);
	}

	void Renderer::setMat4(const std::string& name, const glm::mat4& mat4, bool normalize)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, normalize, &mat4[0][0]);
	}

	bool Renderer::compileShader(unsigned int& shader, unsigned int shaderType, const char* shaderSourceCode, const char* path)
	{
		shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &shaderSourceCode, nullptr);
		glCompileShader(shader);

		int result;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int infoLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);

			char* errorInfo = new char[infoLength];
			glGetShaderInfoLog(shader, infoLength, &infoLength, errorInfo);
			std::string shaderTypeStr;
			if (shaderType == GL_VERTEX_SHADER)
			{
				shaderTypeStr = "VERTEX_SHADER";
			}
			else if (shaderType == GL_GEOMETRY_SHADER)
			{
				shaderTypeStr = "GEOMETRY_SHADER";
			}
			else if(shaderType == GL_FRAGMENT_SHADER)
			{
				shaderTypeStr = "FRAGMENT_SHADER";
			}
			else
			{
				shaderTypeStr = "UnKnown";
			}
			LOG_ERROR("{0} Compile {1} failed:{2}", path, shaderTypeStr, errorInfo);
			delete[] errorInfo;

			glDeleteShader(shader);
			return false;
		}

		return true;
	}

	int Renderer::getUniformLocation(const std::string& name)
	{
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
			return m_uniformLocationCache[name];

		int location;
		location = glGetUniformLocation(m_renderId, name.c_str());
		m_uniformLocationCache[name] = location;
		if (location == -1)
		{
			LOG_ERROR("uniform: " + name + " doesn't exist (or never use)");
		}
		return location;
	}
}