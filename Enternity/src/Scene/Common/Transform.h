#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace Enternity
{
	class Transform
	{
	public:
		glm::vec3 m_Translation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Rotation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Scale{ 1.0f, 1.0f, 1.0f };

		void Move(float distance, const glm::vec3& direction)
		{
			m_Translation += distance * direction;
		}

		void MoveXAxis(float distance)
		{
			Move(distance, GetRotationMatrix()[0]);
		}

		void MoveZAxis(float distance)
		{
			Move(distance, GetRotationMatrix()[2]);
		}

		void RotateAlongXAxis(float angle)
		{
			m_Rotation.x -= angle;
			if (m_Rotation.x >= 2 * glm::pi<float>())
			{
				m_Rotation.x -= 2 * glm::pi<float>();
			}

			if (m_Rotation.x <= -2 * glm::pi<float>())
			{
				m_Rotation.x = m_Rotation.x + 2 * glm::pi<float>();
			}
		}

		void RotateAlongYAxis(float angle)
		{
			m_Rotation.y -= angle;
			if (m_Rotation.y >= 2 * glm::pi<float>())
			{
				m_Rotation.y -= 2 * glm::pi<float>();
			}

			if (m_Rotation.y <= -2 * glm::pi<float>())
			{
				m_Rotation.y = m_Rotation.y + 2 * glm::pi<float>();
			}
		}

		glm::mat4 GetTranslationMatrix() const
		{
			return glm::translate(glm::mat4(1.0f), m_Translation);
		}

		glm::mat4 GetRotationMatrix() const
		{
			//RollPitchYaw to quaternion, quaternion to rotation matrix
			return glm::mat4_cast(glm::qua<float>(m_Rotation));
		}

		glm::mat4 GetScaleMatrix() const
		{
			return glm::scale(glm::mat4(1.0f), m_Scale);
		}

		glm::mat4 GetWorldMatrix() const
		{
			return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
		}

		glm::mat4 GetInverseWorldMatrix() const
		{
			return glm::inverse(GetWorldMatrix());
		}
	};
}