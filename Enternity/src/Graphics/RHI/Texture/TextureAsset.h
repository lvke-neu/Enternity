#pragma once
#include "Engine/Asset.h"
#include <string>

namespace Enternity
{
	class Texture;
	class Blob;
	class TextureAsset : public Asset
	{
		friend class Texture;
	public:
		TextureAsset(const std::string& fullPath);
		~TextureAsset();
	public:
		Blob* getBlob() const;
	private:
		virtual void doLoad() override;
	private:
		std::string m_fullPath{ "" };
		Blob* m_content{ nullptr };
		int m_width{ 0 };
		int m_height{ 0 };
		int m_channels{ 0 };
	};

	inline Blob* TextureAsset::getBlob() const
	{
		return m_content;
	}
}

