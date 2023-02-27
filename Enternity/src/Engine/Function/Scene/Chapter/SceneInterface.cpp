#include "SceneInterface.h"
#include "Core/Basic/Macro.h"
#include "Function/Scene/Camera/Camera3D.h"
#include "Common/Vertex.h"

namespace Enternity
{
	IScene::IScene()
	{
		m_camera3D = new Camera3D;

		m_vertexBuffer = RenderWrapper::Create<VertexBuffer>();
		m_indexBuffer = RenderWrapper::Create<IndexBuffer>();
		m_vertexArray = RenderWrapper::Create<VertexArray>();
		m_shader = RenderWrapper::Create<Shader>();

		VertexPosColor::Init();
	}

	IScene::~IScene()
	{
		SAFE_DELETE_SET_NULL(m_camera3D);

		RenderWrapper::Destroy(m_vertexBuffer);
		RenderWrapper::Destroy(m_indexBuffer);
		RenderWrapper::Destroy(m_vertexArray);
		RenderWrapper::Destroy(m_shader);
	}
}