#pragma once
#include "Graphics/RHI/RHIAsset.h"

namespace Enternity
{
	class IndexBuffer : public RHIAsset
	{
	public:
		virtual ~IndexBuffer();
	public:
		virtual void load(BlobHolder* blobHolder) override;
		virtual void unload() override;
		void bind();
		void unbind();
		unsigned int getCount();
	private:
		unsigned int m_count;
	};

	inline unsigned int IndexBuffer::getCount()
	{
		return m_count;
	}
}