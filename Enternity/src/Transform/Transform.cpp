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
	UpdateMatrix();
}

void Transform::RotateAlongXAxis(float angle)
{
	m_Rotation.x -= angle;
	UpdateMatrix();
}

void Transform::RotateAlongYAxis(float angle)
{
	m_Rotation.y -= angle;
	UpdateMatrix();
}

mat4 Transform::GetTranslationMatrix() const
{
	return m_TranslationMatrix;
}

mat4 Transform::GetRotationMatrix() const
{
	return m_RotationMatrix;
}

mat4 Transform::GetScaleMatrix() const
{
	return m_ScaleMatrix;
}

mat4 Transform::GetWorldMatrix() const
{
	return m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix;
}

void Transform::UpdateMatrix()
{
	m_TranslationMatrix = translate(mat4(1.0f), m_Translation);

	//m_RotationMatrix = rotate(m_RotationMatrix, m_Rotation.x, vec3(1.0f, 0.0f, 0.0f));
	//m_RotationMatrix = rotate(m_RotationMatrix, m_Rotation.y, vec3(0.0f, 1.0f, 0.0f));
	//m_RotationMatrix = rotate(m_RotationMatrix, m_Rotation.z, vec3(0.0f, 0.0f, 1.0f));

	qua<float> q(m_Rotation);
	m_RotationMatrix = mat4_cast(q) * mat4(1.0f);

	m_ScaleMatrix = scale(mat4(1.0f), m_Scale);


}





END_ENTERNITY

