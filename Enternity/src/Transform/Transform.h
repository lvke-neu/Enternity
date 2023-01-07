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

class Transform
{
public:
	Transform() = default;
	~Transform() = default;
	Transform(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);
	Transform(const Transform&) = default;
	Transform& operator=(const Transform&) = default;
public:
	void Move(float distance, const glm::vec3& direction);
	void RotateAlongXAxis(float angle);
	void RotateAlongYAxis(float angle);
public:
	glm::mat4 GetTranslationMatrix() const;
	glm::mat4 GetRotationMatrix() const;
	glm::mat4 GetScaleMatrix() const;
	glm::mat4 GetWorldMatrix() const;
public:
	GET_SET(glm::vec3, Translation);
	GET_SET(glm::vec3, Rotation);
	GET_SET(glm::vec3, Scale);


	//used for imgui
	float* GetTranslationPointer() { return &m_Translation[0]; }
	float* GetRotationPointer() { return &m_Rotation[0]; }
	float* GetScalePointer() { return &m_Scale[0]; }
private:
	glm::vec3 m_Translation{ 0.0f, 0.0f, 0.0f };
	glm::vec3 m_Rotation{ 0.0f, 0.0f, 0.0f };
	glm::vec3 m_Scale{ 1.0f, 1.0f, 1.0f };
};


END_ENTERNITY

