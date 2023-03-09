#pragma once
#include "RuntimeModule/Interface/IRuntimeModule.h"

namespace Enternity
{
	class Asset;
	class AssetManager : public IRuntimeModule
	{
	public:
		virtual ~AssetManager() = default;

		virtual bool Initialize() override;
		virtual void Finalize() override;
		virtual void Tick() override;
	public:
		void loadAsset(Asset& asset);
	private:
		void loadAssetImpl(Asset& asset);

	};
}