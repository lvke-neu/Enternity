#include "Shader.h"
#include <fstream>
#include <sstream>
#include "Log/Log.h"

BEGIN_ENTERNITY

Shader::Shader(const std::string& filePath)
{
	ShaderSourceCode shaderSourceCode;
	if (!ParseShaderFile(shaderSourceCode, filePath))
		return;
	m_rendererId = CreateProgram(shaderSourceCode.VertexShaderSourceCode, shaderSourceCode.PixelShaderSourceCode);
}

Shader::~Shader()
{
	CHECK_GL_CALL(glDeleteProgram(m_rendererId));
}

void Shader::Bind(unsigned int slot) const
{
	CHECK_GL_CALL(glUseProgram(m_rendererId));
}

void Shader::UnBind() const
{
	CHECK_GL_CALL(glUseProgram(0));
}


void Shader::SetInteger1(const std::string & name, int value)
{
	CHECK_GL_CALL(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetFloat3(const std::string& name, float v0, float v1, float v2)
{
	CHECK_GL_CALL(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetFloat3(const std::string& name, const glm::vec3& v3)
{
	SetFloat3(name, v3.x, v3.y, v3.z);
}

void Shader::SetFloat4(const std::string & name, float v0, float v1, float v2, float v3)
{
	CHECK_GL_CALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetFloat4(const std::string& name, const glm::vec4& v4)
{
	SetFloat4(name, v4.x, v4.y, v4.z, v4.w);
}

void Shader::SetMat4f(const std::string & name, const glm::mat4 & mat4)
{
	CHECK_GL_CALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat4[0][0]));
}

int Shader::GetUniformLocation(const std::string & name)
{
	if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
		return m_uniformLocationCache[name];

	int location;
	CHECK_GL_CALL(location = glGetUniformLocation(m_rendererId, name.c_str()));
	m_uniformLocationCache[name] = location;
	if (location == -1)
	{
		LOG_ERROR("uniform: " + name + " doesn't exist (or never use)");
	}
	return location;
}


bool Shader::ParseShaderFile(ShaderSourceCode& shaderSourceCode, const std::string& filePath)
{
	std::ifstream ifs(filePath);
	if (!ifs.is_open())
		return false;

	enum  class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		PIXEL = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType shaderType = ShaderType::NONE;
	while (getline(ifs, line))
	{
		if (line.find("shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				shaderType = ShaderType::VERTEX;
			}
			else if (line.find("pixel") != std::string::npos)
			{
				shaderType = ShaderType::PIXEL;
			}
		}
		else
		{
			ss[(int)shaderType] << line << "\n";
		}
	}

	shaderSourceCode = { ss[0].str(), ss[1].str() };
	ifs.close();

	return true;
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

unsigned int Shader::CreateProgram(const std::string& vsShaderCode, const std::string& psShaderCode)
{
	CHECK_GL_CALL(unsigned int program = glCreateProgram());
	unsigned int vsShader = CompileShader(GL_VERTEX_SHADER, vsShaderCode.c_str());
	unsigned int psShader = CompileShader(GL_FRAGMENT_SHADER, psShaderCode.c_str());

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


END_ENTERNITY