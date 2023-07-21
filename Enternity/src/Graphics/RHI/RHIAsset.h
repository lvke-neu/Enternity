#pragma once
#include "Engine/Asset.h"

namespace Enternity
{
	class RHIAsset : public Asset
	{
	public:
		virtual ~RHIAsset() = default;
	protected:
		unsigned int m_renderId;
	};
}