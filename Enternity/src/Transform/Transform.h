/***************************************************************************************
Author: lvke
Date:2023/1/2 14:27
Description:
Transform 
****************************************************************************************/
#pragma once
#include "Macro/Macro.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

BEGIN_ENTERNITY

using namespace glm;

class Transform
{
public:
	Transform() = default;
	~Transform() = default;
	Transform(const vec3& translation, const vec3& rotation, const vec3& scale);
	Transform(const Transform&) = default;
	Transform& operator=(const Transform&) = default;
public:
	void Move(float distance, const vec3& direction);
	void RotateAlongXAxis(float angle);
	void RotateAlongYAxis(float angle);
public:
	mat4 GetTranslationMatrix() const;
	mat4 GetRotationMatrix() const;
	mat4 GetScaleMatrix() const;
	mat4 GetWorldMatrix() const;
public:
	GET_SET(vec3, Translation);
	GET_SET(vec3, Rotation);
	GET_SET(vec3, Scale);
private:
	vec3 m_Translation{ 0.0f, 0.0f, 0.0f };
	vec3 m_Rotation{ 0.0f, 0.0f, 0.0f };
	vec3 m_Scale{ 1.0f, 1.0f, 1.0f };
};


END_ENTERNITY

