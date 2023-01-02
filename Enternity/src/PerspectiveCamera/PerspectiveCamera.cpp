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