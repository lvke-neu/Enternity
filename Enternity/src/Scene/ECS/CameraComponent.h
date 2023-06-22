#pragma once
#include <glm/gtc/matrix_transform.hpp>

struct CameraComponent
{
	float fovy = 60.0f;
	float aspect = 1.0f;
	float nearZ = 1.0f;
	float farZ = 1000.0f;

	glm::mat4 getProjectionMatrix()
	{
		return glm::perspective<float>(glm::radians(fovy), aspect, nearZ, farZ);
	}
};