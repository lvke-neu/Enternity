#pragma once
#include <functional>
#include <vector>

namespace Enternity
{
	class RHIAsset;
	class BlobHolder;
	class RHIAssetProvider
	{
	private:
		struct BlobHolder_Callback
		{
			BlobHolder* blobHolder;
			std::function<void(RHIAsset*)> callback;
		};
	public:
		RHIAssetProvider();
		virtual ~RHIAssetProvider();

		void getRHIAsset(const char* path, std::function<void(RHIAsset*)> callback);
	private:
		virtual void tick(void* data) = 0;
	protected:
		std::vector<BlobHolder_Callback> m_task;
	};
}