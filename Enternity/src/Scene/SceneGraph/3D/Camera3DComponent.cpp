#include "Camera3DComponent.h"
#include <rttr/registration>

namespace Enternity
{
	Camera3DComponent::Camera3DComponent() :
		m_fovy(60.0f),
		m_aspect(1.0f),
		m_nearz(1.0f),
		m_farz(1000.0f),
		m_speed(10.0f)
	{

	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<Camera3DComponent>("Camera3DComponent")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("fovy", &Camera3DComponent::get_fovy, &Camera3DComponent::set_fovy)
			.property("aspect", &Camera3DComponent::get_aspect, &Camera3DComponent::set_aspect)
			.property("nearz", &Camera3DComponent::get_nearz, &Camera3DComponent::set_nearz)
			.property("farz", &Camera3DComponent::get_farz, &Camera3DComponent::set_farz)
			.property("speed", &Camera3DComponent::get_speed, &Camera3DComponent::set_speed);
	}
}