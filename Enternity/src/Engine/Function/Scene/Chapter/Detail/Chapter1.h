#pragma once
#include "Function/Scene/Chapter/SceneInterface.h"

namespace Enternity
{
	class Chapter1 : public IScene
	{
	public:
		Chapter1();
		virtual ~Chapter1();

		virtual void tick(float deltaTime) override;
	};
}