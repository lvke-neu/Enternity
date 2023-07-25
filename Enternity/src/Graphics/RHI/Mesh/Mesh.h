#pragma once
#include "Graphics/RHI/RHIAsset.h"

namespace Enternity
{
	class Mesh : public RHIAsset
	{
	public:
		virtual ~Mesh();
	public:
		virtual void load(BlobHolder* blobHolder) override;
		virtual void unload() override;
	public:
		void draw();
	private:
		void bind();
		void unbind();
	private:
		unsigned int m_vbId;
		unsigned int m_ibId;
		unsigned int m_count;
	};
}