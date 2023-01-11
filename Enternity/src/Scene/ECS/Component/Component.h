/***************************************************************************************
Author: lvke
Date:2023/1/10 21:01
Description:
Components
****************************************************************************************/
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Macro/Macro.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"


BEGIN_ENTERNITY

struct TransformComponent
{
	glm::vec3 m_Translation{ 0.0f, 0.0f, 0.0f };
	glm::vec3 m_Rotation{ 0.0f, 0.0f, 0.0f };
	glm::vec3 m_Scale{ 1.0f, 1.0f, 1.0f };

	TransformComponent() = default;
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
	{
		m_Translation = translation;
		m_Rotation = rotation;
		m_Scale = scale;
	}

	void Move(float distance, const glm::vec3& direction)
	{
		m_Translation += distance * direction;
	}

	void MoveXAxis(float distance)
	{
		Move(distance,GetRotationMatrix()[0]);
	}

	void MoveZAxis(float distance)
	{
		Move(distance, GetRotationMatrix()[2]);
	}

	void RotateAlongXAxis(float angle)
	{
		m_Rotation.x -= angle;
	}

	void RotateAlongYAxis(float angle)
	{
		m_Rotation.y -= angle;
	}

	glm::mat4 GetTranslationMatrix() const
	{
		return glm::translate(glm::mat4(1.0f), m_Translation);
	}

	glm::mat4 GetRotationMatrix() const
	{
		//RollPitchYaw to quaternion, quaternion to rotation matrix
		return glm::mat4_cast(glm::qua<float>(m_Rotation));
	}

	glm::mat4 GetScaleMatrix() const
	{
		return glm::scale(glm::mat4(1.0f), m_Scale);
	}

	glm::mat4 GetWorldMatrix() const
	{
		return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
	}

	glm::mat4 GetInverseWorldMatrix() const
	{
		return glm::inverse(GetWorldMatrix());
	}
};

struct MeshComponent
{
	VertexArray* m_VertexArray{ nullptr };
	VertexBuffer* m_Vertexbuffer{ nullptr };
	IndexBuffer* m_Indexbuffer{ nullptr };
	Shader* m_Shader{ nullptr };
	Texture* m_Texture{ nullptr };

	MeshComponent() = default;
	MeshComponent( const MeshComponent&) = default;
	MeshComponent(VertexArray* vertexArray,  VertexBuffer* vertexBuffer,  IndexBuffer* indexBuffer, 
		 Shader* shader,  Texture* texture)
	{
		m_VertexArray = vertexArray;
		m_Vertexbuffer = vertexBuffer;
		m_Indexbuffer = indexBuffer;
		m_Shader = shader;
		m_Texture = texture;
	}
	~MeshComponent()
	{
		SAFE_DELETE_SET_NULL(m_VertexArray);
		SAFE_DELETE_SET_NULL(m_Vertexbuffer);
		SAFE_DELETE_SET_NULL(m_Indexbuffer);
		SAFE_DELETE_SET_NULL(m_Shader);
		SAFE_DELETE_SET_NULL(m_Texture);
	}
};

//only store the projectmatrix
struct CameraComponent
{
	glm::mat4 m_ProjectMatrix{ 1.0f };

	CameraComponent() = default;
	CameraComponent(const CameraComponent&) = default;
	CameraComponent(const glm::mat4& projectMatrix)
	{
		m_ProjectMatrix = projectMatrix;
	}
};

END_ENTERNITY