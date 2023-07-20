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
	public:
		RendererBlobHolder(BlobLoader* blobLoader, const std::string& path);
	private:
		std::set<ShaderType> m_shaderTypes;
	};

}