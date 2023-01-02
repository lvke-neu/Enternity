/***************************************************************************************
Author: lvke
Date:2023/1/2 14:27
Description:
Perspective Camera
****************************************************************************************/
#pragma once
#include "Macro/Macro.h"
#include "Transform/Transform.h"

BEGIN_ENTERNITY

struct  Frustum
{
	float FovAngleY = pi<float>() / 3.0f;
	float AspectRatio = 0.5f;
	float NearZ = 1.0f;
	float FarZ = 1000.0f;
};

class PerspectiveCamera
{
	SINGLETON(PerspectiveCamera);
	PRIVATE_FUCNTION(PerspectiveCamera);
public:
	void Initialize(const Transform& transform, const Frustum& frustum);

	void MoveXAxis(float distance);
	void MoveZAxis(float distance);

	void SetTransform(const Transform& transform);
	void SetFrustum(const Frustum& frustum);

	mat4 GetViewMatrix() const;
	mat4 GetProjectMatrix() const;
private:
	Transform m_Transform;
	Frustum m_Frustum;
};

END_ENTERNITY