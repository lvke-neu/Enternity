#pragma once
#include "AssetID.h"

namespace Enternity
{
	class Blob;
	class BlobHolder
	{
	public:
		enum LoadingState
		{
			loading_state_pending,
			loading_state_succeeded,
			loading_state_failed
		};
	public:
		BlobHolder(const AssetID& assetID);
		virtual ~BlobHolder();
	public:
		void load();
	private:
		virtual void doLoad() = 0;
	protected:
		Blob* m_blob;
		LoadingState m_state;
		AssetID m_assetID;
	};
}