#pragma once
#include "Core/Math/Vector2.h"
#include "Core/Math/Vector3.h"
#include "Function/Scene/AssetImpl/ShaderAssetImpl.h"
#include "Function/Scene/AssetImpl/MeshAssetImpl.h"
#include "Function/Scene/AssetImpl/TextureAssetImpl.h"
#include "Core/Memory/Blob.h"
#include "Function/Render/Wrapper/RenderWrapper.h"


namespace Enternity
{
	struct MeshComponent
	{
		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;

		MeshAssetImpl* m_MeshAssetImpl{ nullptr };
	};

	struct ShaderComponent
	{
		ShaderComponent() = default;
		ShaderComponent(const ShaderComponent&) = default;
	
		ShaderAssetImpl* m_shaderAssetImpl{ nullptr };
	};

	struct MaterialComponent
	{
		MaterialComponent() = default;
		MaterialComponent(const MaterialComponent&) = default;

		TextureAssetImpl* m_textureAssetImpl{ nullptr };
	};

	struct AsynLoadTestComponent
	{
		AsynLoadTestComponent() = default;
		AsynLoadTestComponent(const AsynLoadTestComponent&) = default;

		std::string m_texture = "assets/textures/skybox.jpeg";
		Texture2D* m_texture2D{ nullptr };

		void load()
		{
			unLoad();
			m_texture2D = RenderWrapper::Create<Texture2D>();
			m_texture2D->init(m_blob);
			SAFE_DELETE_SET_NULL(m_blob);
		}

		void unLoad()
		{
			RenderWrapper::Destroy(m_texture2D);
		}
	public:
		Blob* m_blob = nullptr;
	};
}