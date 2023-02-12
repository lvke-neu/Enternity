#include "Camera3D.h"

namespace Enternity
{
	Vector3f Camera3D::getPosition()
	{
		return m_position;
	}

	void Camera3D::setPosition(const Vector3f& vec3)
	{
		m_position = vec3;
	}

	Vector3f Camera3D::getRotation()
	{
		return m_rotation;
	}

	void Camera3D::setRotation(const Vector3f& vec3)
	{
		m_rotation = vec3;
	}

	Frustum Camera3D::getFrustum()
	{
		return m_frustum;
	}

	void Camera3D::setFrustum(const Frustum& frustum)
	{
		m_frustum = frustum;
	}

	Matrix4x4f Camera3D::getViewMatrix()
	{
		Matrix4x4f transMat4 = Matrix4x4f::Translate(m_position.x, m_position.y, m_position.z);
		Matrix4x4f rotMat4 = Matrix4x4f::Rotate(m_rotation.x, m_rotation.y, m_rotation.z);
		return Matrix4x4f::Inverse(transMat4 * rotMat4);
	}

	Matrix4x4f Camera3D::getProjMatrix()
	{
		return Matrix4x4f::Perspective(m_frustum.radian, m_frustum.aspect, m_frustum.nearZ, m_frustum.farZ);
	}
}