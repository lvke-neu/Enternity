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

		unsigned int getCount();
	private:
		unsigned int m_vbId;
		unsigned int m_ibId;
		unsigned int m_count;
	};

	inline unsigned int VertexArray::getCount()
	{
		return m_count;
	}
}