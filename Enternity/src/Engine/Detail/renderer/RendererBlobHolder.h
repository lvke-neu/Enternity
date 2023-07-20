#pragma once
#include "Engine/BlobHolder.h"
#include <set>

namespace Enternity
{
	class RendererBlobHolder : public BlobHolder
	{
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
		ShaderDesc getShaderDesc();
		const std::set<ShaderType>& getShaderTypes();
	private:
		std::set<ShaderType> m_shaderTypes;
		ShaderDesc m_shaderDesc;
	};

	inline RendererBlobHolder::ShaderDesc RendererBlobHolder::getShaderDesc()
	{
		return m_shaderDesc;
	}

	inline const std::set<RendererBlobHolder::ShaderType>& RendererBlobHolder::getShaderTypes()
	{
		return m_shaderTypes;
	}
}