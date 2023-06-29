#pragma once
#include <functional>
#include <vector>

namespace Enternity
{
	class Texture;
	class CubeMapTexture;
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

		CubeMapTexture* getCubeMapTexture(const std::vector<const char*>& fullPaths);
	private:
		void tick(void* data);
	private:
		std::vector <TextureAsset_Callback > m_map;
	};
}