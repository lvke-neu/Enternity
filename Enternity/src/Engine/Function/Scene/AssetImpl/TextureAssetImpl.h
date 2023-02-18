/***************************************************************************************
Author: lvke
Date:2023/2/18 17:29
Description:
TextureAssetImpl
****************************************************************************************/
#pragma once
#include "Core/Asset/Asset.h"

namespace Enternity
{
	class IEvent;
	class Texture2D;
	class TextureAssetImpl 
	{
	public:
		TextureAssetImpl();
		~TextureAssetImpl();
		void load(const std::string& matFilePath);
		void unLoad();

		inline Texture2D* getTexture2D();
	protected:
		void loadImpl(IEvent* event);
	private:
		Asset m_textureAsset;

		Texture2D* m_texture2D{ nullptr };
	};

	inline Texture2D* TextureAssetImpl::getTexture2D()
	{
		return m_texture2D;
	}
}