#pragma once
#include <string>
#include <unordered_map>

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
	private:
		unsigned int compileShader(unsigned int shaderType, const char* shaderSourceCode);
		unsigned int createProgram(const char* vsShaderCode, const char* psShaderCode);
		int getUniformLocation(const std::string& name);
	private:
		unsigned int m_renderId;
		std::unordered_map<std::string, int> m_uniformLocationCache;
	};
}