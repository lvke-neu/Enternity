#pragma once
#include "Core/Math/Vector2.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix4x4.h"
#include "Core/File/Blob.h"
#include "Function/Render/Wrapper/RenderWrapper.h"

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

		VertexArray* m_VertexArray{ nullptr };
		VertexBuffer* m_Vertexbuffer{ nullptr };
		IndexBuffer* m_Indexbuffer{ nullptr };
	};

	struct MaterialComponent
	{
		MaterialComponent() = default;
		MaterialComponent(const MaterialComponent&) = default;

		std::string m_vsShader{ "" };
		std::string m_psShader{ "" };
		Shader* m_shader{ nullptr };

		void syncLoad()
		{

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