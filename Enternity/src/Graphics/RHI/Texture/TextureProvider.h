#pragma once

namespace Enternity
{
	class Texture;
	class TextureProvider
	{
	public:
		Texture* getTexture(const char* fullPath);
	};
}