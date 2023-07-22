#pragma once

namespace Enternity
{
	class BlobHolder;
	class Asset
	{
	public:
		enum LoadingState
		{
			loading_state_pending,
			loading_state_succeeded,
			loading_state_failed
		};
	public:
		virtual ~Asset() = default;
	public:
		virtual void load(BlobHolder* blobHolder) = 0;
		virtual void unload() = 0;
		bool isLoadSucceeded();
	protected:
		LoadingState m_state{ loading_state_pending };
	};

	inline bool Asset::isLoadSucceeded()
	{
		return loading_state_succeeded == m_state;
	}
}