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
	//	rttr::registration::class_<Visual3DComponent>("Visual3DComponent")
	//		.constructor<>()
	//		(
	//			rttr::policy::ctor::as_raw_ptr
	//		)
	//		.property("texture", &Visual3DComponent::get_texture, &Visual3DComponent::set_texture)
	//		.property("renderer", &Visual3DComponent::get_renderer, &Visual3DComponent::set_renderer)
	//		.property("color", &Visual3DComponent::get_color, &Visual3DComponent::set_color)
	//		.property("postprocess", &Visual3DComponent::get_postprocess, &Visual3DComponent::set_postprocess);

	//rttr::registration::enumeration<Color>("Color")
	//	(
	//		rttr::detail::enum_data("Red", Color::Red),
	//		rttr::detail::enum_data("Green", Color::Green),
	//		rttr::detail::enum_data("Blue", Color::Blue)
	//	);

	//rttr::registration::enumeration<Postprocess>("Postprocess")
	//	(
	//		rttr::detail::enum_data("Gray", Postprocess::Gray),
	//		rttr::detail::enum_data("Blur", Postprocess::Blur)
	//		);
	}
}