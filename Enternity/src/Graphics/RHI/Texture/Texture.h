#pragma once
#include <vector>

namespace Enternity
{
	class TextureAsset;
	class Texture
	{
	public:
		Texture(TextureAsset* textureAsset);
		~Texture();
	public:
		unsigned int getRenderId();
		void bind(unsigned int slot);
		void unbind();
	private:
		unsigned int m_renderId;
	};

	inline unsigned int Texture::getRenderId()
	{
		return m_renderId;
	}


	class CubeMapTexture
	{
	public:
		CubeMapTexture(const std::vector<TextureAsset*>& textureAssets);
		~CubeMapTexture();
	public:
		unsigned int getRenderId();
		void bind(unsigned int slot);
		void unbind();
	private:
		unsigned int m_renderId;
	};

	inline unsigned int CubeMapTexture::getRenderId()
	{
		return m_renderId;
	}
}