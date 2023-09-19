#include "Material.h"

namespace Enternity
{
	RTTR_REGISTRATION
	{
		rttr::registration::class_<Material>("Material")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("ambientColor", &Material::get_ambientColor, &Material::set_ambientColor)
			.property("diffuseColor", &Material::get_diffuseColor, &Material::set_diffuseColor)
			.property("specularColor", &Material::get_specularColor, &Material::set_specularColor);
	}
}