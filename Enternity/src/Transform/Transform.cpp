#include "Transform.h"
#include <glm/gtc/quaternion.hpp>

BEGIN_ENTERNITY

Transform::Transform(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale):
	m_Translation(translation), m_Rotation(rotation), m_Scale(scale)
{

}

void Transform::Move(float distance, const glm::vec3& direction)
{
	m_Translation += distance * direction;
}

void Transform::RotateAlongXAxis(float angle)
{
	m_Rotation.x -= angle;
}

void Transform::RotateAlongYAxis(float angle)
{
	m_Rotation.y -= angle;
}

glm::mat4 Transform::GetTranslationMatrix() const
{
	return glm::translate(glm::mat4(1.0f), m_Translation);
}

glm::mat4 Transform::GetRotationMatrix() const
{
	//RollPitchYaw to quaternion, quaternion to rotation matrix
	return glm::mat4_cast(glm::qua<float>(m_Rotation));
}

glm::mat4 Transform::GetScaleMatrix() const
{
	return glm::scale(glm::mat4(1.0f), m_Scale);
}

glm::mat4 Transform::GetWorldMatrix() const
{
	return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
}

END_ENTERNITY

