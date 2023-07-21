#pragma once
#include "Graphics/RHI/RHIAssetProvider.h"

namespace Enternity
{
	class RendererProvider : public RHIAssetProvider
	{
	public:
		RendererProvider();
	private:
		virtual void tick(void* data) override;
	};
}