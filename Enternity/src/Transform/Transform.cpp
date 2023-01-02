#include "Transform.h"
#include <glm/gtc/quaternion.hpp>

BEGIN_ENTERNITY

Transform::Transform(const vec3& translation, const vec3& rotation, const vec3& scale):
	m_Translation(translation), m_Rotation(rotation), m_Scale(scale)
{

}

void Transform::Move(float distance, const vec3& direction)
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

mat4 Transform::GetTranslationMatrix() const
{
	return translate(mat4(1.0f), m_Translation);
}

mat4 Transform::GetRotationMatrix() const
{
	//RollPitchYaw to quaternion, quaternion to rotation matrix
	return mat4_cast(qua<float>(m_Rotation));
}

mat4 Transform::GetScaleMatrix() const
{
	return scale(mat4(1.0f), m_Scale);
}

mat4 Transform::GetWorldMatrix() const
{
	return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
}

END_ENTERNITY

