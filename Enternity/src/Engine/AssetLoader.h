#pragma once
#include <functional>
#include <vector>

namespace Enternity
{
	class Asset;
	class BlobLoader;
	class BlobHolder;
	class AssetLoader
	{
		friend class Engine;
	private:
		struct BlobHolder_Callback
		{
			BlobHolder* blobHolder;
			std::function<void(Asset*)> callback;
		};
	private:
		AssetLoader();
		~AssetLoader();
	private:
		void tick(void* data);
	public:
		void getAsset(const char* path, std::function<void(Asset*)> callback);
		Asset* getAsset(const char* path);
	protected:
		std::vector<BlobHolder_Callback> m_task;
	};
}