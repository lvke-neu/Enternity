#pragma once
#include "Engine/Asset2.h"
#include <string>

namespace Enternity
{
	class Texture;
	class Blob;
	class TextureAsset : public Asset2
	{
		friend class Texture;
		friend class CubeMapTexture;
	public:
		TextureAsset(const std::string& fullPath, bool slip = true);
		TextureAsset(Blob* data, int width, int height, int channels);
		~TextureAsset();
	public:
		Blob* getBlob() const;
		int getWidth();
		int getHeight();
	private:
		virtual void doLoad() override;
	private:
		std::string m_fullPath{ "" };
		Blob* m_content{ nullptr };
		int m_width{ 0 };
		int m_height{ 0 };
		int m_channels{ 0 };
		bool m_bSlip = true;
	};

	inline Blob* TextureAsset::getBlob() const
	{
		return m_content;
	}

	inline int TextureAsset::getWidth()
	{
		return m_width;
	}

	inline int TextureAsset::getHeight()
	{
		return m_height;
	}
}

