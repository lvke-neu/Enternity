#pragma once
#include "Core/Math/Vector2.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix4x4.h"
#include "Core/File/Blob.h"
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

		std::string m_meshFile{ "" };
		VertexArray* m_vertexArray{ nullptr };
		VertexBuffer* m_vertexbuffer{ nullptr };
		IndexBuffer* m_indexbuffer{ nullptr };

		void loadImpl()
		{
			if (m_vertexbufferBlob && m_indexbufferBlob)
			{
				unLoad();

				m_vertexArray = RenderWrapper::Create<VertexArray>();
				m_vertexbuffer = RenderWrapper::Create<VertexBuffer>();
				m_indexbuffer = RenderWrapper::Create<IndexBuffer>();

				VertexBufferLayout  vertexBufferLayout;
				vertexBufferLayout.push({ 0, 3, GL_FLOAT, false,  8 * sizeof(float), 0 });
				vertexBufferLayout.push({ 1, 3, GL_FLOAT, false,  8 * sizeof(float), 3 * sizeof(float) });
				vertexBufferLayout.push({ 2, 2, GL_FLOAT, false,  8 * sizeof(float), 6 * sizeof(float) });
				m_vertexbuffer->init(m_vertexbufferBlob, vertexBufferLayout);
				m_indexbuffer->init(m_indexbufferBlob);
				m_vertexArray->init(m_vertexbuffer);
				
				SAFE_DELETE_SET_NULL(m_vertexbufferBlob);
				SAFE_DELETE_SET_NULL(m_indexbufferBlob);

			}
		}

		void unLoad()
		{
			RenderWrapper::Destroy(m_vertexArray);
			RenderWrapper::Destroy(m_vertexbuffer);
			RenderWrapper::Destroy(m_indexbuffer);
		}
	public:
		Blob* m_vertexbufferBlob{ nullptr };
		Blob* m_indexbufferBlob{ nullptr };
	};

	struct ShaderComponent
	{
		ShaderComponent() = default;
		ShaderComponent(const ShaderComponent&) = default;

		std::string m_vsShaderFile{ "" };
		std::string m_psShaderFile{ "" };
		Shader* m_shader{ nullptr };

		void loadImpl()
		{
			if (m_vsBlob && m_psBlob)
			{
				unLoad();
				m_shader = RenderWrapper::Create<Shader>();
				m_shader->init(m_vsBlob, m_psBlob);
				SAFE_DELETE_SET_NULL(m_vsBlob);
				SAFE_DELETE_SET_NULL(m_psBlob);
			}
		}

		void unLoad()
		{
			RenderWrapper::Destroy(m_shader);
		}
	public:
		Blob* m_vsBlob{ nullptr };
		Blob* m_psBlob{ nullptr };
	};


	struct MaterialComponent
	{
		MaterialComponent() = default;
		MaterialComponent(const MaterialComponent&) = default;

		std::string m_textureFile{ "" };
		Texture2D* m_texture2D{ nullptr };

		void loadImpl()
		{
			if (m_textureBlob)
			{
				unLoad();
				m_texture2D = RenderWrapper::Create<Texture2D>();
				m_texture2D->init(m_textureBlob);
				SAFE_DELETE_SET_NULL(m_textureBlob);
			}
		}

		void unLoad()
		{
			RenderWrapper::Destroy(m_texture2D);
		}
	public:
		Blob* m_textureBlob = nullptr;
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