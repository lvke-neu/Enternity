#pragma once
#include <functional>
#include <vector>

namespace Enternity
{
	class Texture;
	class TextureAsset;
	class TextureProvider
	{
		struct TextureAsset_Callback
		{
			TextureAsset* textureAsset;
			std::function<void(Texture*)> callback;
		};
	public:
		TextureProvider();
		~TextureProvider();
	public:
		Texture* getTextureSync(const char* fullPath);
		void  getTextureAsyn(const char* fullPath, std::function<void(Texture*)> callback);
	private:
		void tick(void* data);
	private:
		std::vector <TextureAsset_Callback > m_map;
	};
}