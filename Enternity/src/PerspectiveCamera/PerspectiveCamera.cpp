#include "PerspectiveCamera.h"

BEGIN_ENTERNITY

void PerspectiveCamera::Initialize(const Transform& transform, const Frustum& frustum)
{
	m_Transform = transform;
	m_Frustum = frustum;
}

void PerspectiveCamera::MoveXAxis(float distance)
{
	m_Transform.Move(distance, m_Transform.GetRotationMatrix()[0]);
}

void PerspectiveCamera::MoveZAxis(float distance)
{
	m_Transform.Move(distance, m_Transform.GetRotationMatrix()[2]);
}

void PerspectiveCamera::RotateAlongXAxis(float angle)
{
	m_Transform.RotateAlongXAxis(angle);
}

void PerspectiveCamera::RotateAlongYAxis(float angle)
{
	m_Transform.RotateAlongYAxis(angle);
}

const glm::vec3 & PerspectiveCamera::GetTranslation() const
{
	return m_Transform.GetTranslation();
}

void PerspectiveCamera::SetTranslation(const glm::vec3 & translation)
{
	m_Transform.SetTranslation(translation);
}

const glm::vec3 & PerspectiveCamera::GetRotation() const
{
	return m_Transform.GetRotation();
}

void PerspectiveCamera::SetRotation(const glm::vec3 & rotation)
{
	m_Transform.SetRotation(rotation);
}

const glm::vec3 & PerspectiveCamera::GetScale() const
{
	return m_Transform.GetScale();
}

void PerspectiveCamera::SetScale(const glm::vec3 & scale)
{
	m_Transform.SetScale(scale);
}

glm::mat4 PerspectiveCamera::GetViewMatrix() const
{
	return glm::inverse(m_Transform.GetWorldMatrix());
}

glm::mat4 PerspectiveCamera::GetProjectMatrix() const
{
	return glm::perspective<float>(m_Frustum.FovAngleY, m_Frustum.AspectRatio, m_Frustum.NearZ, m_Frustum.FarZ);
}



END_ENTERNITY