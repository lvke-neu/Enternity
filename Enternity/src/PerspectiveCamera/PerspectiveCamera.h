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
	float FovAngleY = glm::pi<float>() / 3.0f;
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
	void RotateAlongXAxis(float angle);
	void RotateAlongYAxis(float angle);
public:
	GET_SET(Transform, Transform);
	GET_SET(Frustum, Frustum);

	const glm::vec3& GetTranslation() const;
	void SetTranslation(const glm::vec3& translation);

	const glm::vec3& GetRotation() const;
	void SetRotation(const glm::vec3& rotation);

	const glm::vec3& GetScale() const;
	void SetScale(const glm::vec3& scale);

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectMatrix() const;

	float* GetTranslationPointer() { return m_Transform.GetTranslationPointer(); }
	float* GetRotationPointer() { return m_Transform.GetRotationPointer(); }
	float* GetScalePointer() { return m_Transform.GetScalePointer(); }
private:
	Transform m_Transform;
	Frustum m_Frustum;
};

END_ENTERNITY