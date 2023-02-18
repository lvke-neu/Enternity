#pragma once
#include "Core/Math/Vector2.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix4x4.h"
#include "Core/Asset/Asset.h"
#include "Core/Memory/Blob.h"
#include "Function/Render/Wrapper/RenderWrapper.h"
#include <glad/glad.h>

namespace Enternity
{
	struct TransformComponent
	{
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;

		Vector3f m_position = Vector3f::ZERO;
		Vector3f m_rotation = Vector3f::ZERO;
		Vector3f m_scale	= Vector3f::ONE;

		Matrix4x4f getWorldMatrix()
		{
			return Matrix4x4f::Translate(m_position.x, m_position.y, m_position.z) *
				Matrix4x4f::Rotate(m_rotation.x, m_rotation.y, m_rotation.z)*
				Matrix4x4f::Scale(m_scale.x, m_scale.y, m_scale.z);
		}
	};

	struct MeshComponent
	{
		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;

		struct VertexPosNorTex
		{
			Vector3f position;
			Vector3f normal;
			Vector2f texcoord;
		};

		Asset m_meshAsset;

		VertexArray* m_vertexArray{ nullptr };
		VertexBuffer* m_vertexbuffer{ nullptr };
		IndexBuffer* m_indexbuffer{ nullptr };

		void loadImpl()
		{
			if (m_meshAsset.getAssetLoadState() == AssetLoadState::success)
			{
				unLoad();

				m_vertexArray = RenderWrapper::Create<VertexArray>();
				m_vertexbuffer = RenderWrapper::Create<VertexBuffer>();
				m_indexbuffer = RenderWrapper::Create<IndexBuffer>();

				VertexBufferLayout  vertexBufferLayout;
				vertexBufferLayout.push({ 0, 3, GL_FLOAT, false,  8 * sizeof(float), 0 });
				vertexBufferLayout.push({ 1, 3, GL_FLOAT, false,  8 * sizeof(float), 3 * sizeof(float) });
				vertexBufferLayout.push({ 2, 2, GL_FLOAT, false,  8 * sizeof(float), 6 * sizeof(float) });
				m_vertexbuffer->init(m_meshAsset.getBlob()[0], vertexBufferLayout);
				m_indexbuffer->init(m_meshAsset.getBlob()[1]);
				m_vertexArray->init(m_vertexbuffer);
				
				m_meshAsset.reset();
			}
		}

		void unLoad()
		{
			RenderWrapper::Destroy(m_vertexArray);
			RenderWrapper::Destroy(m_vertexbuffer);
			RenderWrapper::Destroy(m_indexbuffer);
		}		
	};

	struct ShaderComponent
	{
		ShaderComponent() = default;
		ShaderComponent(const ShaderComponent&) = default;

		Asset m_vsAsset;
		Asset m_psAsset;

		Shader* m_shader{ nullptr };

		void loadImpl()
		{
			if (m_vsAsset.getAssetLoadState() == AssetLoadState::success &&
				m_psAsset.getAssetLoadState() == AssetLoadState::success)
			{
				unLoad();
				m_shader = RenderWrapper::Create<Shader>();
				m_shader->init(m_vsAsset.getBlob()[0], m_psAsset.getBlob()[0]);
				m_vsAsset.reset();
				m_psAsset.reset();
			}
		}

		void unLoad()
		{
			RenderWrapper::Destroy(m_shader);
		}
	};

	struct MaterialComponent
	{
		MaterialComponent() = default;
		MaterialComponent(const MaterialComponent&) = default;

		Asset m_materialAsset;
		
		Texture2D* m_texture2D{ nullptr };

		void loadImpl()
		{
			if (m_materialAsset.getAssetLoadState() == AssetLoadState::success)
			{
				unLoad();
				m_texture2D = RenderWrapper::Create<Texture2D>();
				m_texture2D->init(m_materialAsset.getBlob()[0]);
				m_materialAsset.reset();
			}
		}

		void unLoad()
		{
			RenderWrapper::Destroy(m_texture2D);
		}
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