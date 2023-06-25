#pragma once
#include "RenderPass.h"
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
		const std::string& getVsShader() const;
		const std::string& getPsShader() const;
		RenderPass getRenderPass() const;
		void setRenderPass(RenderPass renderPass);
		void applyRenderPass();
		void reCompile();
	private:
		unsigned int compileShader(unsigned int shaderType, const char* shaderSourceCode);
		unsigned int createProgram(const char* vsShaderCode, const char* psShaderCode);
		int getUniformLocation(const std::string& name);
	private:
		unsigned int m_renderId;
		std::unordered_map<std::string, int> m_uniformLocationCache;

		std::string m_vsShader{ "" };
		std::string m_psShader{ "" };

		RenderPass m_renderPass;
	};

	inline const std::string& Renderer::getVsShader() const
	{
		return m_vsShader;
	}

	inline const std::string& Renderer::getPsShader() const
	{
		return m_psShader;
	}

	inline RenderPass Renderer::getRenderPass() const
	{
		return m_renderPass;
	}

	inline void Renderer::setRenderPass(RenderPass renderPass)
	{
		m_renderPass = renderPass;
	}
}