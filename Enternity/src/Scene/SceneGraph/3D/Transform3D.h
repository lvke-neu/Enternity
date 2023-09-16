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
	public:
		void move(float distance, const glm::vec3& direction)
		{
			m_translation += distance * direction;
		}

		void moveXAxis(float distance)
		{
			move(distance, getRotationMatrix()[0]);
		}

		void moveZAxis(float distance)
		{
			move(distance, getRotationMatrix()[2]);
		}

		void rotateAlongXAxis(float angle)
		{
			m_rotation.x -= angle;
		}

		void rotateAlongYAxis(float angle)
		{
			m_rotation.y -= angle;
		}

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