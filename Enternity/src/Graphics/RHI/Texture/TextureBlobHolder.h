#pragma once
#include "Engine/BlobHolder.h"

namespace Enternity
{
	//#########################################################################################
	class TextureBlobHolder : public BlobHolder
	{
	public:
		TextureBlobHolder(BlobLoader* blobLoader, const char* path);
		virtual ~TextureBlobHolder() = default;
		enum TextureType
		{
			None,
			Texture_2D,
			Texture_2D_HDR,
			Texture_Cube_Map,
			Texture_Cube_Map_HDR,
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
		virtual ~Texture2DBlobHolder() = default;
		virtual Asset* createAsset() override;
	public:
		int getWidth();
		int getHeight();
		int getChannels();
		void setSlip(bool flag);
	protected:
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

	
	class Texture2DHDRBlobHolder : public Texture2DBlobHolder
	{
		friend class Texture2DHDR;
		friend class TextureBlobLoader;
	public:
		Texture2DHDRBlobHolder(BlobLoader* blobLoader, const char* path);
		virtual Asset* createAsset() override;
	};

	//#########################################################################################
	class TextureCubeMapBlobHolder : public TextureBlobHolder
	{
		friend class TextureCubeMap;
		friend class TextureBlobLoader;
	public:
		TextureCubeMapBlobHolder(BlobLoader* blobLoader, const char* path);
		virtual ~TextureCubeMapBlobHolder();
		virtual Asset* createAsset() override;
	private:
		Texture2DBlobHolder* m_texture2DBlobHolders[6];
		std::string m_paths[6];
	};

	//#########################################################################################
	class MeshBlobHolder;
	class RendererBlobHolder;
	class Texture2DHDRBlobHolder;
	class TextureCubeMapHDRBlobHolder : public TextureBlobHolder
	{
		friend class TextureCubeMapHDR;
		friend class TextureBlobLoader;
	public:
		TextureCubeMapHDRBlobHolder(BlobLoader* blobLoader, const char* path);
		virtual ~TextureCubeMapHDRBlobHolder();
		virtual Asset* createAsset() override;
	private:
		MeshBlobHolder* m_meshBlobHolder;
		RendererBlobHolder* m_rendererBlobHolder;
		Texture2DHDRBlobHolder* m_texture2DHDRBlobHolder;
	};
}