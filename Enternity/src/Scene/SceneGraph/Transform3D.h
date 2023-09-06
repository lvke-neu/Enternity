#pragma once
#include <glm/gtc/quaternion.hpp>

namespace Enternity
{
	class Transform3D
	{
	public:
		glm::mat4 getTranslationMatrix() const;
		glm::mat4 getRotationMatrix() const;
		glm::mat4 getScaleMatrix() const;
		glm::mat4 getWorldMatrix() const;
		glm::mat4 getInverseWorldMatrix() const;
	private:
		glm::vec3 m_translation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_rotation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_scale{ 1.0f, 1.0f, 1.0f };
	};
}