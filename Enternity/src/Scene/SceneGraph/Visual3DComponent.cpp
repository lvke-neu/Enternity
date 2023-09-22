#include "Visual3DComponent.h"
#include "Node3D.h"
#include "Visual3D.h"

namespace Enternity
{
	Visual3DComponent::Visual3DComponent(Visual3D* visual3D) : m_visual3D(visual3D)
	{

	}

	Visual3DComponent::~Visual3DComponent()
	{
		SAFE_DELETE_SET_NULL(m_visual3D);
	}

	void Visual3DComponent::command()
	{	
		ENTERNITY_ASSERT(m_visual3D);

		if (!m_enable)
		{
			return;
		}
		m_visual3D->draw();
	}

	void Visual3DComponent::onAttachToNode(Node* node)
	{
		ENTERNITY_ASSERT(m_visual3D);
		m_visual3D->set_node((Node3D*)node);
	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<Visual3DComponent>("Visual3DComponent")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("visual3Ds", &Visual3DComponent::get_visual3D, &Visual3DComponent::set_visual3D);
	}
}