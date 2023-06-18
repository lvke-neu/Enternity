#pragma once

namespace Enternity
{
	class TextureAsset;
	class Texture
	{
	public:
		Texture(TextureAsset* textureAsset);
		~Texture();
	//TODO:remove
	private:
		int m_width{ 0 };
		int m_height{ 0 };
		int m_channels{ 0 };
	};
}