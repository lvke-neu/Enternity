/***************************************************************************************
Author: lvke
Date:2023/2/12 9:49
Description:
Editor Camera
****************************************************************************************/
#pragma once
#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix4x4.h"
#include "Core/Math/Math.h"

namespace Enternity
{
	struct Frustum
	{
		float radian;
		float aspect;
		float nearZ;
		float farZ;
	};

	class Camera3D
	{
	public:
		Vector3f getPosition();
		void setPosition(const Vector3f& vec3);

		Vector3f getRotation();
		void setRotation(const Vector3f& vec3);

		Frustum getFrustum();
		void setFrustum(const Frustum& frustum);

		Matrix4x4f getViewMatrix();
		Matrix4x4f getProjMatrix();
	private:
		Vector3f m_position = Vector3f::ZERO;
		//degree
		Vector3f m_rotation = Vector3f::ZERO;
		Frustum m_frustum{ PI / 6.0f, 2.0f, 1.0f, 1000.0f };
	};
}