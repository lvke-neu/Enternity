#include "Transform3D.h"

namespace Enternity
{
	Transform3D::Transform3D() :
		m_translation(glm::vec3(0.0f)),
		m_rotation(glm::vec3(0.0f)),
		m_scale(glm::vec3(1.0f))
	{

	}

	glm::mat4 Transform3D::getTranslationMatrix() const
	{
		return glm::translate(glm::mat4(1.0f), m_translation);
	}

	glm::mat4 Transform3D::getRotationMatrix() const
	{
		//rollPitchYaw to quaternion, quaternion to rotation matrix
		return glm::mat4_cast(glm::qua<float>(glm::radians(m_rotation)));
	}

	glm::mat4 Transform3D::getScaleMatrix() const
	{
		return glm::scale(glm::mat4(1.0f), m_scale);
	}

	glm::mat4 Transform3D::getWorldMatrix() const
	{
		return getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();
	}

	glm::mat4 Transform3D::getInverseWorldMatrix() const
	{
		return glm::inverse(getWorldMatrix());
	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<Transform3D>("Transform3D")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("translation", &Transform3D::get_translation, &Transform3D::set_translation)
			.property("rotation", &Transform3D::get_rotation, &Transform3D::set_rotation)
			.property("scale", &Transform3D::get_scale, &Transform3D::set_scale);
	}
}