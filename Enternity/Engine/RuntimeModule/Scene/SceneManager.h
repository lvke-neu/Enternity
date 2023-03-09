#pragma once
#include "RuntimeModule/Interface/IRuntimeModule.h"
#include <unordered_map>

namespace Enternity
{
	class SceneManager : public IRuntimeModule
	{
	public:
		virtual ~SceneManager() = default;

		virtual bool Initialize() override;
		virtual void Finalize() override;
		virtual void Tick() override;
	};
}