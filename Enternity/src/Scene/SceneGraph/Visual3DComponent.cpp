#include "Visual3DComponent.h"
#include "Node3D.h"
#include "Graphics/Material.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include <glad/glad.h>

namespace Enternity
{
	Visual3DComponent::Visual3DComponent() : m_wireFrame(false), m_mesh(nullptr), m_renderer(nullptr), m_material(nullptr)
	{

	}

	Visual3DComponent::~Visual3DComponent()
	{
		SAFE_DELETE_SET_NULL(m_mesh);
		SAFE_DELETE_SET_NULL(m_renderer);
		SAFE_DELETE_SET_NULL(m_material);
	}

	void Visual3DComponent::setMesh(Mesh* mesh)
	{
		if (!mesh || m_mesh == mesh)
		{
			return;
		}

		SAFE_DELETE_SET_NULL(m_mesh);
		m_mesh = mesh;
	}

	void Visual3DComponent::setRenderer(Renderer* renderer)
	{
		if (!renderer || m_renderer == renderer)
		{
			return;
		}

		SAFE_DELETE_SET_NULL(m_renderer);
		m_renderer = renderer;
	}

	void Visual3DComponent::setMaterial(Material* material)
	{
		if (!material || m_material == material)
		{
			return;
		}

		SAFE_DELETE_SET_NULL(m_material);
		m_material = material;
	}

	void Visual3DComponent::command()
	{	
		if (!m_enable)
		{
			return;
		}

		if (ASSET_LOAD_SUCCEED(m_mesh) &&
			ASSET_LOAD_SUCCEED(m_renderer))
		{
			if (m_wireFrame)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}

			m_renderer->bind();
			m_renderer->setMat4("u_model", getNode<Node3D>()->getTransform().getWorldMatrix());
			
			if (m_material && ASSET_LOAD_SUCCEED(m_material->get_ambientTexture()))
			{
				m_material->get_ambientTexture()->bind(0);
			}

			m_mesh->draw();

			if (m_material && ASSET_LOAD_SUCCEED(m_material->get_ambientTexture()))
			{
				m_material->get_ambientTexture()->unbind(0);
			}
			m_renderer->unbind();

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<Visual3DComponent>("Visual3DComponent")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("wireFrame", &Visual3DComponent::get_wireFrame, &Visual3DComponent::set_wireFrame)
			.property("material", &Visual3DComponent::get_material, &Visual3DComponent::set_material);
	}
}