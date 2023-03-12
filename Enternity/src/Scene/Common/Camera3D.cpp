#include "Camera3D.h"
#include "Core/Math/Math.h"

namespace Enternity
{
	Vector3f& Camera3D::getPosition()
	{
		return m_translation;
	}

	void Camera3D::setPosition(const Vector3f& vec3)
	{
		m_translation = vec3;
	}

	Vector3f& Camera3D::getRotation()
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
		Matrix4x4f rotateMatrix;
		Matrix4x4RotateYawPitchRoll(rotateMatrix, m_rotation.x, m_rotation.y, m_rotation.z, false);
		Matrix4x4f translateMatrix;
		Matrix4x4Translate(translateMatrix, m_translation.x, m_translation.y, m_translation.z);

		return Matrix4x4Inverse(translateMatrix * rotateMatrix);
	}

	Matrix4x4f Camera3D::getProjMatrix()
	{
		Matrix4x4f projMatrix;
		Matrix4x4Perspective(projMatrix, m_frustum.fov, m_frustum.aspect, m_frustum.nearZ, m_frustum.farZ, false);
		return projMatrix;
	}

	void Camera3D::move(float dis, const Vector3f& dir)
	{
		m_translation += dir * dis;
	}

	void Camera3D::moveForward(float dis)
	{
		Matrix4x4f rotMat4;
		Matrix4x4RotateYawPitchRoll(rotMat4, m_rotation.x, m_rotation.y, m_rotation.z, false);

		Vector3f dir(rotMat4[2][0], rotMat4[2][1], rotMat4[2][2]);
		dir.z = -dir.z;
		move(dis, dir);
	}

	void Camera3D::moveRight(float dis)
	{
		//Matrix4x4f rotMat4 = Matrix4x4f::Rotate(Math::Radian(m_rotation.x), Math::Radian(m_rotation.y), Math::Radian(m_rotation.z));
		//Vector3f dir = rotMat4[0];
		//dir.z = -dir.z;
		//move(dis, dir);
	}

	void Camera3D::rotateAlongXAxis(float angle)
	{
		//m_rotation.x -= angle;

		////if (m_rotation.x >= 2 * PI)
		////{
		////	m_rotation.x -= 2 * PI;
		////}

		////if (m_rotation.x <= -2 * PI)
		////{
		////	m_rotation.x = m_rotation.x + 2 * PI;
		////}
	}

	void Camera3D::rotateAlongYAxis(float angle)
	{
		//m_rotation.y -= angle;

		////if (m_rotation.y >= 2 * PI)
		////{
		////	m_rotation.y -= 2 * PI;
		////}

		////if (m_rotation.y <= -2 * PI)
		////{
		////	m_rotation.y = m_rotation.y + 2 * PI;
		////}
	}
}