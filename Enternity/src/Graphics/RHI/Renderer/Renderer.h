#pragma once
#include "Graphics/RHI/RHIAsset.h"

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
	private:
		bool compileShader(unsigned int& shader, unsigned int shaderType, const char* shaderSourceCode, const char* path);
	};
}