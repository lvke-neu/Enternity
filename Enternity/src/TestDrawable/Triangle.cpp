#include "Triangle.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

BEGIN_ENTERNITY

struct ShaderSourceCode
{
	std::string VertexShaderSourceCode;
	std::string PixelShaderSourceCode;
};

ShaderSourceCode ParseShaderFile(const std::string& filePath)
{
	std::ifstream ifs(filePath);

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
	return { ss[0].str(), ss[1].str() };
}

unsigned int CompileShader(unsigned int shaderType, const char* shaderSourceCode)
{
	unsigned int shader;
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
		std::cout << errorInfo << std::endl;
		delete[] errorInfo;

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

unsigned int CreateProgram(const std::string& vsShaderCode, const std::string& psShaderCode)
{
	unsigned int program = glCreateProgram();
	unsigned int vsShader = CompileShader(GL_VERTEX_SHADER, vsShaderCode.c_str());
	unsigned int psShader = CompileShader(GL_FRAGMENT_SHADER, psShaderCode.c_str());

	glAttachShader(program, vsShader);
	glAttachShader(program, psShader);
	glLinkProgram(program);
	glValidateProgram(program);

	int result;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		int infoLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);

		char* errorInfo = new char[infoLength];
		glGetProgramInfoLog(program, infoLength, &infoLength, errorInfo);
		std::cout << errorInfo << std::endl;
		delete[] errorInfo;

		glDeleteProgram(program);
		return 0;
	}

	glDeleteShader(vsShader);
	glDeleteShader(psShader);

	return program;
}

Triangle::Triangle()
{
	//vertexbuff
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f, 1.0f,0.0f,0.0f,
		 0.5f, -0.5,  0.0f, 0.0f,1.0f,0.0f,
		 0.5f, 0.5,  0.0f,  0.0f,0.0f,1.0f,
		 -0.5f, 0.5f, 0.0f, 0.0f,0.0f,1.0f
	};
	vertexbuffer = new VertexBuffer(vertices, sizeof(vertices));

	//vertex array
	vertexArray = new VertexArray;
	VertexBufferLayout  vertexBufferLayout;
	vertexBufferLayout.Push({ 0, 3, GL_FLOAT, false,  6 * sizeof(float), 0 });
	vertexBufferLayout.Push({ 1, 3, GL_FLOAT, false,  6 * sizeof(float), 3 * sizeof(float) });
	vertexArray->Add(*vertexbuffer, vertexBufferLayout);

	//index buffer
	unsigned int indices[] =
	{ 0,1,2,2,3,0 };

	indexbuffer = new IndexBuffer(indices, 6);

	//shader
	ShaderSourceCode shaderSourceCode;
	shaderSourceCode = ParseShaderFile("shader/Basic.shader");
	program = CreateProgram(shaderSourceCode.VertexShaderSourceCode, shaderSourceCode.PixelShaderSourceCode);
}

void Triangle::draw()
{
	CHECK_GL_CALL(glUseProgram(program));
	CHECK_GL_CALL(glUniform4f(0, 1.0f, 0.0f, 0.0f, 1.0f));
	vertexArray->Bind();
	indexbuffer->Bind();
	CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, indexbuffer->GetCount(), GL_UNSIGNED_INT, (void*)0));
}

Triangle::~Triangle()
{
	SAFE_DELETE_SET_NULL(vertexbuffer);
	SAFE_DELETE_SET_NULL(indexbuffer);
	SAFE_DELETE_SET_NULL(vertexArray);
}

END_ENTERNITY