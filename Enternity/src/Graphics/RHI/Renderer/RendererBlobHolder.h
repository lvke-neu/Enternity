#pragma once
#include "Engine/BlobHolder.h"
#include <set>

namespace Enternity
{
	class RendererBlobHolder : public BlobHolder
	{
		friend class Renderer;
		friend class RendererBlobLoader;
	public:
		enum ShaderType
		{
			VertexShader,
			GeometryShader,
			FragmentShader
		};
		struct ShaderDesc
		{
			unsigned int vertDataOffset;
			unsigned int vertDataSize;
			unsigned int geomDataOffset;
			unsigned int geomDataSize;
			unsigned int fragDataOffset;
			unsigned int fragDataSize;
		};
	public:
		RendererBlobHolder(BlobLoader* blobLoader, const std::string& path);
		virtual Asset* createAsset() override;
	private:
		std::set<ShaderType> m_shaderTypes;
		ShaderDesc m_shaderDesc;
	};
}