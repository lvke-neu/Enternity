#pragma once
#include "Graphics/RHI/RHIAsset.h"

namespace Enternity
{
	class Renderer : public RHIAsset
	{
	public:
		virtual void load(BlobHolder* blobHolder) override;
	private:
		unsigned int m_renderId;
	};
}