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
		struct TextureAsset_Callback2
		{
			std::vector<TextureAsset*> textureAssets;
			std::function<void(CubeMapTexture*)> callback;
		};
	public:
		TextureProvider();
		~TextureProvider();
	public:
		Texture* getTextureSync(const char* fullPath);
		void  getTextureAsyn(const char* fullPath, std::function<void(Texture*)> callback);

		CubeMapTexture* getCubeMapTextureSync(const std::vector<const char*>& fullPaths);
		void getCubeMapTextureAsyn(const std::vector<const char*>& fullPaths, std::function<void(CubeMapTexture*)> callback);
	private:
		void tick(void* data);
	private:
		std::vector <TextureAsset_Callback > m_map;
		std::vector <TextureAsset_Callback2 > m_map2;
	};
}