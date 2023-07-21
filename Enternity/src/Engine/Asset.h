#pragma once

namespace Enternity
{
	class BlobHolder;
	class Asset
	{
	public:
		virtual ~Asset() = default;
	public:
		virtual void load(BlobHolder* blobHolder) = 0;
	};
}