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
#include <glm/gtx/matrix_decompose.hpp>
#include "Macro/Macro.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "File/FileOperation.h"

BEGIN_ENTERNITY

struct TagComponent
{
	TagComponent() = default;
	TagComponent(const TagComponent&) = default;
	TagComponent(const std::string& tag)
	{
		m_Tag = tag;
	}
	std::string m_Tag{ "" };
};

//test 
struct MotorComponent
{
	float m_RotationYAnglePerSecond = 45.0f;
	float m_RotationXAnglePerSecond = 45.0f;
	MotorComponent() = default;
	MotorComponent(const MotorComponent&) = default;
	MotorComponent(float angleY, float angleX)
	{
		m_RotationYAnglePerSecond = angleY;
		m_RotationXAnglePerSecond = angleX;
	}
};

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
		if (m_Rotation.x >= 2 * glm::pi<float>())
		{
			m_Rotation.x -= 2 * glm::pi<float>();
		}

		if (m_Rotation.x <= -2 * glm::pi<float>())
		{
			m_Rotation.x = m_Rotation.x + 2 * glm::pi<float>();
		}
	}

	void RotateAlongYAxis(float angle)
	{
		m_Rotation.y -= angle;
		if (m_Rotation.y >= 2 * glm::pi<float>())
		{
			m_Rotation.y -= 2 * glm::pi<float>();
		}

		if (m_Rotation.y <= -2 * glm::pi<float>())
		{
			m_Rotation.y = m_Rotation.y + 2 * glm::pi<float>();
		}
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

	std::string m_MeshFilePath{ "" };

	MeshComponent() = default;
	MeshComponent(const MeshComponent&) = default;

	void LoadMesh(const std::string& meshFilePath)
	{
		
		m_MeshFilePath = meshFilePath;
		struct VertexPosTex
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 texcoord;
		};
		std::string suffix = meshFilePath.substr(meshFilePath.find("."), meshFilePath.size() - 1);
		if (suffix != ".mesh")
			return;

		Enternity::Blob blob2(DEFAULT_BLOB_LENGTH);
		if (!Enternity::FileOperation::ReadFile(blob2, meshFilePath))
			return;

		UnLoad();
		unsigned int vertexcount2;
		unsigned int indexcount2;
		memcpy_s(&vertexcount2, sizeof(unsigned int), blob2.GetData(), sizeof(unsigned int));
		memcpy_s(&indexcount2, sizeof(unsigned int), (char*)blob2.GetData() + sizeof(unsigned int), sizeof(unsigned int));

		VertexPosTex* vpt = new VertexPosTex[vertexcount2];
		unsigned int* indices2 = new unsigned int[indexcount2];
		memcpy_s(vpt, vertexcount2 * sizeof(VertexPosTex), (char*)blob2.GetData() + 2 * sizeof(unsigned int), vertexcount2 * sizeof(VertexPosTex));
		memcpy_s(indices2, indexcount2 * sizeof(unsigned int), (char*)blob2.GetData() + 2 * sizeof(unsigned int) + vertexcount2 * sizeof(VertexPosTex), indexcount2 * sizeof(unsigned int));


		m_Vertexbuffer = new VertexBuffer(vpt, vertexcount2 * sizeof(VertexPosTex));
		m_VertexArray = new VertexArray;
		VertexBufferLayout  vertexBufferLayout;
		vertexBufferLayout.Push({ 0, 3, GL_FLOAT, false,  8 * sizeof(float), 0 });
		vertexBufferLayout.Push({ 1, 3, GL_FLOAT, false,  8 * sizeof(float), 3 * sizeof(float) });
		vertexBufferLayout.Push({ 2, 2, GL_FLOAT, false,  8 * sizeof(float), 6 * sizeof(float) });
		m_VertexArray->Add(*m_Vertexbuffer, vertexBufferLayout);
		m_Indexbuffer = new IndexBuffer(indices2, indexcount2);

		delete[] vpt;
		delete[] indices2;
	}

	void UnLoad()
	{
		SAFE_DELETE_SET_NULL(m_VertexArray);
		SAFE_DELETE_SET_NULL(m_Vertexbuffer);
		SAFE_DELETE_SET_NULL(m_Indexbuffer);
	}
};


struct MaterialComponent
{
	Shader* m_Shader{ nullptr };
	Texture* m_Texture{ nullptr };

	std::string m_TextureFilePath{ "" };
	std::string m_ShaderFilePath{ "" };

	bool m_bUseColor = false;
	glm::vec4 m_BaseColor{ 1.0f };

	MaterialComponent()
	{
		LoadShader("assets/shaders/TestECS.glsl");
		SetBaseColor(glm::vec4{ 1.0f });
	}
	MaterialComponent(const MaterialComponent&) = default;


	void LoadTexture(const std::string& textureFilePath)
	{
		SAFE_DELETE_SET_NULL(m_Texture);
		m_TextureFilePath = textureFilePath;
		m_Texture = new Texture(textureFilePath);
	}

	void LoadShader(const std::string& shaderFilePath)
	{
		SAFE_DELETE_SET_NULL(m_Shader);
		m_ShaderFilePath = shaderFilePath;
		m_Shader = new Shader(shaderFilePath);
		SetIsUseColor(m_bUseColor);
		SetBaseColor(m_BaseColor);
	}

	void LoadMaterial(const std::string& textureFilePath, const std::string& shaderFilePath)
	{
		LoadTexture(textureFilePath);
		LoadShader(shaderFilePath);
	}

	void SetIsUseColor(bool b_useColor)
	{
		m_bUseColor = b_useColor;
		m_Shader->Bind();
		m_Shader->SetInteger1("b_useColor", b_useColor);
	}

	void SetBaseColor(const glm::vec4& baseColor)
	{
		m_BaseColor = baseColor;;
		m_Shader->Bind();
		m_Shader->SetFloat4("u_baseColor", baseColor);
	}

	void SetMaterialProperty(bool b_useColor, const glm::vec4& baseColor, unsigned int textureSlot)
	{
		m_bUseColor = b_useColor;
		m_BaseColor = baseColor;

		m_Shader->Bind();
		m_Shader->SetInteger1("b_useColor", b_useColor);
		m_Shader->SetFloat4("u_baseColor", baseColor);
		m_Shader->SetInteger1("u_texture", textureSlot);
	}
	

	void UnLoad()
	{
		SAFE_DELETE_SET_NULL(m_Shader);
		SAFE_DELETE_SET_NULL(m_Texture);
	}
};

//only store the projectmatrix
struct CameraComponent
{
	glm::mat4 m_ProjectMatrix{ 1.0f };
	float m_MoveSpeed = 10.0f;
	bool m_EnableWireframe = false;

	float m_Fovy = 60.0f;
	float m_Aspect = 1.0f;
	float m_NearZ = 1.0f;
	float m_FarZ = 1000.0f;

	void ReCalculateProjectMatrix()
	{
		m_ProjectMatrix = glm::perspective<float>(glm::radians(m_Fovy), m_Aspect, m_NearZ, m_FarZ);
	}

	void InitStateByAllProperty()
	{
		ReCalculateProjectMatrix();
		if (m_EnableWireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	CameraComponent() = default;
	CameraComponent(const CameraComponent&) = default;

};

END_ENTERNITY