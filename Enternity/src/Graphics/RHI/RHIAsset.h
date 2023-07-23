#pragma once
#include "Engine/Asset.h"

namespace Enternity
{
	class RHIAsset : public Asset
	{
	public:
		virtual ~RHIAsset() = default;
		unsigned int getRenderId();
	protected:
		unsigned int m_renderId;
	};

	inline unsigned int RHIAsset::getRenderId()
	{
		return m_renderId;
	}
}