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
	private:
		struct BlobHolder_Callback
		{
			BlobHolder* blobHolder;
			std::function<void(Asset*)> callback;
		};
	public:
		AssetLoader();
		virtual ~AssetLoader();

		void getAsset(const char* path, std::function<void(Asset*)> callback);
	private:
		void tick(void* data);
	protected:
		std::vector<BlobHolder_Callback> m_task;
	};
}