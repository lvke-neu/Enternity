#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Enternity
{
	class RendererAsset;
	class Renderer
	{
	public:
		Renderer(RendererAsset* vsRendererAsset, RendererAsset* psRendererAsset, RendererAsset* gsRendererAsset = nullptr);
		~Renderer();
	public:
		void bind();
		void unbind();
	public:
		void setMat4(const std::string& name, const glm::mat4& mat4, bool normalize = false);
	private:
		unsigned int compileShader(unsigned int shaderType, const char* shaderSourceCode);
		unsigned int createProgram(const char* vsShaderCode, const char* psShaderCode);
		int getUniformLocation(const std::string& name);
	private:
		unsigned int m_renderId;
		std::unordered_map<std::string, int> m_uniformLocationCache;
	};
}