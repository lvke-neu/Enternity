#pragma once
#include "RuntimeModule/Interface/IRuntimeModule.h"

namespace Enternity
{
	enum class AseetLoadType
	{
		Sync,
		Asyn
	};

	class Asset;
	class AssetManager : public IRuntimeModule
	{
	public:
		virtual ~AssetManager() = default;

		virtual bool Initialize() override;
		virtual void Finalize() override;
		virtual void Tick() override;
	public:
		void loadAsset(Asset& asset, AseetLoadType type);
	private:
		void loadAssetImpl(Asset& asset);
	};
}