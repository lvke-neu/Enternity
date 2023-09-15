#pragma once
#include "Engine/Reference.h"
#include <glm/gtc/quaternion.hpp>

namespace Enternity
{
	class Transform3D : public Reference
	{
		RTTR_ENABLE(Reference);
	public:
		Transform3D();
	public:
		GET_CLASS_NAME(Component);
	public:
		GET_SET(glm::vec3, translation);
		GET_SET(glm::vec3, rotation);
		GET_SET(glm::vec3, scale);
		glm::mat4 getTranslationMatrix() const;
		glm::mat4 getRotationMatrix() const;
		glm::mat4 getScaleMatrix() const;
		glm::mat4 getWorldMatrix() const;
		glm::mat4 getInverseWorldMatrix() const;
	private:
		glm::vec3 m_translation;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
	};
}