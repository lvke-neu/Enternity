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

Transform & PerspectiveCamera::GetTransform()
{
	return m_Transform;
}

void PerspectiveCamera::SetTransform(const Transform & transform)
{
	m_Transform = transform;
}

void PerspectiveCamera::SetFrustum(const Frustum & frustum)
{
	m_Frustum = frustum;
}

mat4 PerspectiveCamera::GetViewMatrix() const
{
	return inverse(m_Transform.GetWorldMatrix());
}

mat4 PerspectiveCamera::GetProjectMatrix() const
{
	return perspective<float>(m_Frustum.FovAngleY, m_Frustum.AspectRatio, m_Frustum.NearZ, m_Frustum.FarZ);
}



END_ENTERNITY