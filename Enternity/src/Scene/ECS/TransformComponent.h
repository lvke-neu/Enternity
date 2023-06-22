#pragma once
#include <glm/gtc/quaternion.hpp>

namespace Enternity
{
	struct TransformComponent
	{
		glm::vec3 translation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 scale{ 1.0f, 1.0f, 1.0f };

		void move(float distance, const glm::vec3& direction)
		{
			translation += distance * direction;
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
			rotation.x -= angle;
			if (rotation.x >= 2 * glm::pi<float>())
			{
				rotation.x -= 2 * glm::pi<float>();
			}

			if (rotation.x <= -2 * glm::pi<float>())
			{
				rotation.x = rotation.x + 2 * glm::pi<float>();
			}
		}

		void rotateAlongYAxis(float angle)
		{
			rotation.y -= angle;
			if (rotation.y >= 2 * glm::pi<float>())
			{
				rotation.y -= 2 * glm::pi<float>();
			}

			if (rotation.y <= -2 * glm::pi<float>())
			{
				rotation.y = rotation.y + 2 * glm::pi<float>();
			}
		}

		glm::mat4 getTranslationMatrix() const
		{
			return glm::translate(glm::mat4(1.0f), translation);
		}

		glm::mat4 getRotationMatrix() const
		{
			//rollPitchYaw to quaternion, quaternion to rotation matrix
			return glm::mat4_cast(glm::qua<float>(rotation));
		}

		glm::mat4 getScaleMatrix() const
		{
			return glm::scale(glm::mat4(1.0f), scale);
		}

		glm::mat4 getWorldMatrix() const
		{
			return getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();
		}

		glm::mat4 getInverseWorldMatrix() const
		{
			return glm::inverse(getWorldMatrix());
		}
	};
}