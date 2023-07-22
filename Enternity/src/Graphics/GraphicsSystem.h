#pragma once
#include "RenderSystem.h"

namespace Enternity
{
	class GraphicsSystem : public RenderSystem
	{
		friend class Engine;
	private:
		GraphicsSystem();
		virtual ~GraphicsSystem();
	};
}