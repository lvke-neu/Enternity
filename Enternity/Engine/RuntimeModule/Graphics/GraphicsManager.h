#pragma once

#include "RuntimeModule/Interface/IRuntimeModule.h"

namespace Enternity
{
	class GraphicsManager : public IRuntimeModule
	{
	public:
		virtual ~GraphicsManager() = default;

		virtual bool Initialize() override
		{
			return true;
		}

		virtual void Finalize() override
		{

		}
		virtual void Tick() override
		{

		}
	};
}