#include "Shader.h"
#include "Core/Log/Log.h"
#include "Core/File/Blob.h"
#include <glad/glad.h>

namespace Enternity
{
	void Shader::Destroy()
	{
		CHECK_GL_CALL(glDeleteProgram(m_renderId));
	}

	void Shader::init(Blob* vsBlob, Blob* psBlob)
	{
		ENTERNITY_ASSERT(vsBlob != nullptr && psBlob != nullptr);

		//the end '\0', this code is so ugly !!!!!!!!!!!!!!!
		std::string vsStr((char*)vsBlob->getData(), vsBlob->getLength());
		std::string psStr((char*)psBlob->getData(), psBlob->getLength());
		m_renderId = CreateProgram(vsStr.c_str(), psStr.c_str());
	}

	void Shader::bind()
	{
		CHECK_GL_CALL(glUseProgram(m_renderId));
	}

	void Shader::unbind()
	{
		CHECK_GL_CALL(glUseProgram(0));
	}

	unsigned int Shader::CompileShader(unsigned int shaderType, const char* shaderSourceCode)
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

	unsigned int Shader::CreateProgram(const char* vsShaderCode, const char* psShaderCode)
	{
		CHECK_GL_CALL(unsigned int program = glCreateProgram());

		unsigned int vsShader = CompileShader(GL_VERTEX_SHADER, vsShaderCode);
		unsigned int psShader = CompileShader(GL_FRAGMENT_SHADER, psShaderCode);

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
}



