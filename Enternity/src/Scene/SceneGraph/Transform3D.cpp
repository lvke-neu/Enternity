#include "Transform3D.h"

namespace Enternity
{
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
}