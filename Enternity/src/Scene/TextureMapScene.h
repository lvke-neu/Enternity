#pragma once

#include "Interface/SceneInterface.h"

namespace Enternity
{
	class TextureMapScene : public IScene
	{
	public:
		virtual void Initialize() override;
		virtual void Finalize() override;
		virtual void Tick(float deltaTime) override;
	};
}