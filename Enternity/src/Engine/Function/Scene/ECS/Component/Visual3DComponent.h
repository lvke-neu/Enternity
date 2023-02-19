#pragma once
#include "Function/Scene/AssetImpl/RenderPassAssetImpl.h"
#include "Function/Scene/AssetImpl/MeshAssetImpl.h"
#include "Function/Scene/AssetImpl/TextureAssetImpl.h"

namespace Enternity
{
	struct Visual3DComponent
	{
		Visual3DComponent() = default;
		Visual3DComponent(const Visual3DComponent&) = default;

		MeshAssetImpl* m_MeshAssetImpl{ nullptr };
		RenderPassAssetImpl* m_rendererPassAssetImpl{ nullptr };
		TextureAssetImpl* m_textureAssetImpl{ nullptr };
	};

	struct AsynLoadTestComponent
	{
	//	AsynLoadTestComponent() = default;
	//	AsynLoadTestComponent(const AsynLoadTestComponent&) = default;

	//	std::string m_texture = "assets/textures/skybox.jpeg";
	//	Texture2D* m_texture2D{ nullptr };

	//	void load()
	//	{
	//		unLoad();
	//		m_texture2D = RenderWrapper::Create<Texture2D>();
	//		m_texture2D->init(m_blob);
	//		SAFE_DELETE_SET_NULL(m_blob);
	//	}

	//	void unLoad()
	//	{
	//		RenderWrapper::Destroy(m_texture2D);
	//	}
	//public:
	//	Blob* m_blob = nullptr;
	};
}