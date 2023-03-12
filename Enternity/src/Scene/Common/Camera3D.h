/***************************************************************************************
Author: lvke
Date:2023/2/12 9:49
Description:
Editor Camera
****************************************************************************************/
#pragma once
#include "Core/Math/Matrix.h"

namespace Enternity
{
	struct Frustum
	{
		float fov;
		float aspect;
		float nearZ;
		float farZ;
	};

	class Camera3D
	{
	public:
		Vector3f& getPosition();
		void setPosition(const Vector3f& vec3);

		Vector3f& getRotation();
		void setRotation(const Vector3f& vec3);

		Frustum getFrustum();
		void setFrustum(const Frustum& frustum);

		Matrix4x4f getViewMatrix();
		Matrix4x4f getProjMatrix();

		void move(float dis, const Vector3f& dir);
		void moveForward(float dis);
		void moveRight(float dis);
		void rotateAlongXAxis(float angle);
		void rotateAlongYAxis(float angle);
	private:
		Vector3f m_translation{0.0f, 0.0f, 0.0f};
		Vector3f m_rotation{ 0.0f, 0.0f, 0.0f };
		Frustum m_frustum{ 45.0f, 1.5f, 0.1f, 1000.0f };
	};
}