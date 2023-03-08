#pragma once
#include "RuntimeModule/Interface/IRuntimeModule.h"
#include <unordered_map>

namespace Enternity
{
	class Blob;
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
		void unLoadAsset(const std::string& assetID);
	private:
		void loadAssetImpl(Asset& asset);
	private:
		std::unordered_map<std::string, Blob*> m_cache;
	};
}