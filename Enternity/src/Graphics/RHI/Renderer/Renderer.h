#pragma once
#include "Graphics/RHI/RHIAsset.h"
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
		void setUint1(const std::string& name, unsigned int value);
	private:
		bool compileShader(unsigned int& shader, unsigned int shaderType, const char* shaderSourceCode, const char* path);
		int getUniformLocation(const std::string& name);
	private:
		std::unordered_map<std::string, int> m_uniformLocationCache;
	};
}