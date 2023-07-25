#pragma once
#include "Graphics/RHI/RHIAsset.h"
#include <glm/glm.hpp>
#include <unordered_map>

namespace Enternity
{
	class Renderer : public RHIAsset
	{
	public:
		virtual ~Renderer();
	public:
		virtual void load(BlobHolder* blobHolder) override;
		virtual void unload() override;
		void bind();
		void unbind();
	public:
		void setInt1(const std::string& name, int value);
		void setUint1(const std::string& name, unsigned int value);
		void setMat4(const std::string& name, const glm::mat4& mat4, bool normalize = false);
	private:
		bool compileShader(unsigned int& shader, unsigned int shaderType, const char* shaderSourceCode, const char* path);
		int getUniformLocation(const std::string& name);
	private:
		std::unordered_map<std::string, int> m_uniformLocationCache;
	};
}