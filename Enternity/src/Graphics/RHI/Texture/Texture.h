#pragma once
#include <vector>
#include <string>

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
		const std::vector<std::string>& getFullPaths() const;
	private:
		unsigned int m_renderId;
		std::vector<std::string> m_fullPaths;
	};

	inline unsigned int CubeMapTexture::getRenderId()
	{
		return m_renderId;
	}

	inline const std::vector<std::string>& CubeMapTexture::getFullPaths() const
	{
		return m_fullPaths;
	}
}