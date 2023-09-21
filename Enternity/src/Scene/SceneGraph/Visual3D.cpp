#include "Visual3D.h"
#include "Node3D.h"
#include "Graphics/Material.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include <glad/glad.h>

namespace Enternity
{

	Visual3D::Visual3D() : 
		m_enable(true), 
		m_name(""), 
		m_mesh(nullptr), 
		m_renderer(nullptr), 
		m_material(nullptr)
	{

	}

	void Visual3D::set_mesh(std::shared_ptr<Mesh> mesh)
	{
		m_mesh = mesh;
	}

	void Visual3D::set_renderer(std::shared_ptr<Renderer> renderer)
	{
		m_renderer = renderer;
	}

	void Visual3D::set_material(std::shared_ptr<Material> material)
	{
		m_material = material;
	}

	void Visual3D::draw()
	{
		ENTERNITY_ASSERT(m_node);

		if (!m_enable)
		{
			return;
		}

		if (m_wireFrame)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		if (ASSET_LOAD_SUCCEED(m_mesh) &&
			ASSET_LOAD_SUCCEED(m_renderer))
		{
			m_renderer->bind();
			m_renderer->setMat4("u_model", m_node->getTransform().getWorldMatrix());

			if (m_material)
			{
				m_material->bind(m_renderer.get());
			}

			m_mesh->draw();

			if (m_material)
			{
				m_material->unbind();
			}
			m_renderer->unbind();
		}

		if (m_wireFrame)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<Visual3D>("Visual3D")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("name",&Visual3D::get_name, &Visual3D::set_name)
			.property("enable",&Visual3D::get_enable, &Visual3D::set_enable)
			.property("wireFrame", &Visual3D::get_wireFrame, &Visual3D::set_wireFrame)
			.property("material",&Visual3D::get_material, &Visual3D::set_material);
	}
}