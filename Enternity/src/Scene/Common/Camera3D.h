/***************************************************************************************
Author: lvke
Date:2023/2/12 9:49
Description:
Editor Camera
****************************************************************************************/
#pragma once
#include "Transform.h"

namespace Enternity
{
	class Camera3D
	{
	public:
		Transform m_transform;
		float fov = 45.0f;
		float aspect = 1.5f;
		float nearZ = 0.1f;
		float farZ = 1000.0f;
	};
}