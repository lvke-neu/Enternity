#include "Renderer.h"
#include "RendererBlobHolder.h"
#include "Engine/Blob.h"

namespace Enternity
{
	void Renderer::load(BlobHolder* blobHolder)
	{
		RendererBlobHolder* rendererBlobHolder = dynamic_cast<RendererBlobHolder*>(blobHolder);
		if (!rendererBlobHolder)
		{
			return;
		}

		for (auto type : rendererBlobHolder->getShaderTypes())
		{
			if (type == RendererBlobHolder::VertexShader)
			{
				m_vscode = std::string((char*)rendererBlobHolder->getBlob()->getData() + rendererBlobHolder->getShaderDesc().vertDataOffset,
					rendererBlobHolder->getShaderDesc().vertDataSize);
			}

			if (type == RendererBlobHolder::GeometryShader)
			{
				m_gscode = std::string((char*)rendererBlobHolder->getBlob()->getData() + rendererBlobHolder->getShaderDesc().geomDataOffset,
					rendererBlobHolder->getShaderDesc().geomDataSize);
			}

			if (type == RendererBlobHolder::FragmentShader)
			{
				m_pscode = std::string((char*)rendererBlobHolder->getBlob()->getData() + rendererBlobHolder->getShaderDesc().fragDataOffset,
					rendererBlobHolder->getShaderDesc().fragDataSize);
			}
		}

		m_renderId = 123;
	}
}