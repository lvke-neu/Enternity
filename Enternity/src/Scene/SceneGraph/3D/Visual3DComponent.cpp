#include "Visual3DComponent.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include <rttr/registration>

#include "Scene3D.h"
#include "Node3D.h"
#include "../../SceneManager.h"
#include "Camera3DComponent.h"

namespace Enternity
{
	Visual3DComponent::Visual3DComponent()
	{
		m_meshPath = "mesh://primitive=cube";
		m_rendererPath = "renderer://assets/shaders/visual3d/visual3d.rdr";
		m_texturePath = "texture://TEXTURE_2D?assets/textures/box_diffuse.png";

		m_mesh = (Mesh*)Engine::GetInstance().getAssetLoader()->getAsset(m_meshPath.c_str());
		m_renderer = (Renderer*)Engine::GetInstance().getAssetLoader()->getAsset(m_rendererPath.c_str());
		m_texture = (Texture2D*)Engine::GetInstance().getAssetLoader()->getAsset(m_texturePath.c_str());
	}

	Visual3DComponent::~Visual3DComponent()
	{
		SAFE_DELETE_SET_NULL(m_mesh);
		SAFE_DELETE_SET_NULL(m_renderer);
		SAFE_DELETE_SET_NULL(m_texture);
	}

	void Visual3DComponent::tick()
	{	
		if (!m_enable)
		{
			return;
		}

		auto rootNode = Engine::GetInstance().getSceneManager()->getCurrentScene()->get_rootNode();
		auto model = getNode<Node3D>()->getTransform().getWorldMatrix();
		auto view = ((Node3D*)rootNode->get_childs()[0])->get_transform().getInverseWorldMatrix();
		auto proj = ((Camera3DComponent*)rootNode->get_childs()[0]->get_components()[0])->getProjectionMatrix();

		m_renderer->bind();
		m_renderer->setMat4("u_mvp", proj * view * model);
		m_texture->bind(0);
		m_mesh->draw();
		m_texture->unbind(0);
		m_renderer->unbind();
	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<Visual3DComponent>("Visual3DComponent")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("meshPath", &Visual3DComponent::get_meshPath, &Visual3DComponent::set_meshPath)
			.property("rendererPath", &Visual3DComponent::get_rendererPath, &Visual3DComponent::set_rendererPath)
			.property("texturePath", &Visual3DComponent::get_texturePath, &Visual3DComponent::set_texturePath);

	}
}