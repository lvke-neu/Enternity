#include "Node3D.h"

namespace Enternity
{
	Node3D::Node3D() 
	{
		m_transform.set_translation(glm::vec3(0.0f));
		m_transform.set_rotation(glm::vec3(0.0f));
		m_transform.set_scale(glm::vec3(1.0f));
	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<Node3D>("Node3D")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("transform3D", &Node3D::get_transform, &Node3D::set_transform);
	}
}