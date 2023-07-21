#pragma once
#include "Engine/Asset.h"

namespace Enternity
{
	class RHIAsset : public Asset
	{
	protected:
		unsigned int m_renderId;
	};
}