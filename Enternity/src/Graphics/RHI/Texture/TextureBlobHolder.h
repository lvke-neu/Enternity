#pragma once
#include "Engine/BlobHolder.h"

namespace Enternity
{
	//#########################################################################################
	class TextureBlobHolder : public BlobHolder
	{
	public:
		TextureBlobHolder(BlobLoader* blobLoader, const char* path);
		enum TextureType
		{
			None,
			Texture_2D,
			Texture_Cube_Map
		};
		TextureType getTextureType();
	protected:
		TextureType m_textureType{ None };
	};

	inline TextureBlobHolder::TextureType TextureBlobHolder::getTextureType()
	{
		return m_textureType;
	}

	//#########################################################################################
	class Texture2DBlobHolder : public TextureBlobHolder
	{
		friend class Texture2D;
		friend class TextureBlobLoader;
	public:
		Texture2DBlobHolder(BlobLoader* blobLoader, const char* path);
		virtual Asset* createAsset() override;
	public:
		int getWidth();
		int getHeight();
		int getChannels();
		void setSlip(bool flag);
	private:
		int m_width;
		int m_height;
		int m_channels;
		bool m_bSlip;
	};

	inline void Texture2DBlobHolder::setSlip(bool flag)
	{
		m_bSlip = flag;
	}

	inline int Texture2DBlobHolder::getWidth()
	{
		return m_width;
	}

	inline int Texture2DBlobHolder::getHeight()
	{
		return m_height;
	}

	inline int Texture2DBlobHolder::getChannels()
	{
		return m_channels;
	}

	//#########################################################################################
	class TextureCubeMapBlobHolder : public TextureBlobHolder
	{
		friend class TextureCubeMap;
		friend class TextureBlobLoader;
	public:
		TextureCubeMapBlobHolder(BlobLoader* blobLoader, const char* path);
		virtual Asset* createAsset() override;
	private:
		Texture2DBlobHolder* m_texture2DBlobHolders[6];
		std::string m_paths[6];
	};
}