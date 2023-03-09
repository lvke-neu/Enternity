#pragma once

namespace Enternity
{
	class Blob;
	class AssetLoader;
	class Asset
	{
	public:
		Asset() = default;
		virtual ~Asset() = default;
	public:
		virtual void doLoad() = 0;
		virtual void callBack() = 0;
	};
}