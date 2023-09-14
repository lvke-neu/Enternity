#include "Visual3DComponent.h"
#include <rttr/registration>

namespace Enternity
{

	Visual3DComponent::Visual3DComponent()
	{

	}

	Visual3DComponent::~Visual3DComponent()
	{

	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<Visual3DComponent>("Visual3DComponent")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("texture",&Visual3DComponent::get_texture, &Visual3DComponent::set_texture);
	}
}