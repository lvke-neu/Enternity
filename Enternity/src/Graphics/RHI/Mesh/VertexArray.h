#pragma once
#include "Graphics/RHI/RHIAsset.h"

namespace Enternity
{
	class VertexArray : public RHIAsset
	{
	public:
		virtual ~VertexArray();
	public:
		virtual void load(BlobHolder* blobHolder) override;
		virtual void unload() override;
		void bind();
		void unbind();
	private:
		unsigned int m_vbId;
	};
}