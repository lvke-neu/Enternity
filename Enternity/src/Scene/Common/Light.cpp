#include "Light.h"
#include "Core/Log/Log.h"
#include "Core/Asset/AssetLoader.h"
#include "Core/Blob/Blob.h"
#include "RHI/VertexBuffer.h"
#include "RHI/VertexArray.h"
#include "RHI/IndexBuffer.h"
#include "RHI/Shader.h"
#include "Utility/Utility.h"
#include "Camera3D.h"
#include "Vertex.h"
#include <glad/glad.h>

namespace Enternity
{

	Light::Light(Camera3D* camera3D)
	{
		m_pCamera3D = camera3D;
		m_transform.m_Scale = glm::vec3(0.5f, 0.5f, 0.5f);
		m_transform.m_Translation = glm::vec3(3.0f, 0.0f, 0.0f);
		{
			VertexBuffer tmpVertexBuffer;
			std::vector<VertexPosition> vertices;
			vertices.resize(24);

			//front
			vertices[0].position = Vector3f(-0.5f, 0.5f, 0.5f);
			vertices[1].position = Vector3f(0.5f, 0.5f, 0.5f);
			vertices[2].position = Vector3f(0.5f, -0.5f, 0.5f);
			vertices[3].position = Vector3f(-0.5f, -0.5f, 0.5f);

			//back
			vertices[4].position = Vector3f(-0.5f, 0.5f, -0.5f);
			vertices[5].position = Vector3f(0.5f, 0.5f, -0.5f);
			vertices[6].position = Vector3f(0.5f, -0.5f, -0.5f);
			vertices[7].position = Vector3f(-0.5f, -0.5f, -0.5f);

			//left
			vertices[8].position = Vector3f(-0.5f, 0.5f, -0.5f);
			vertices[9].position = Vector3f(-0.5f, 0.5f, 0.5f);
			vertices[10].position = Vector3f(-0.5f, -0.5f, 0.5f);
			vertices[11].position = Vector3f(-0.5f, -0.5f, -0.5f);

			//right
			vertices[12].position = Vector3f(0.5f, 0.5f, -0.5f);
			vertices[13].position = Vector3f(0.5f, 0.5f, 0.5f);
			vertices[14].position = Vector3f(0.5f, -0.5f, 0.5f);
			vertices[15].position = Vector3f(0.5f, -0.5f, -0.5f);

			//top
			vertices[16].position = Vector3f(-0.5f, 0.5f, -0.5f);
			vertices[17].position = Vector3f(0.5f, 0.5f, -0.5f);
			vertices[18].position = Vector3f(0.5f, 0.5f, 0.5f);
			vertices[19].position = Vector3f(-0.5f, 0.5f, 0.5f);

			//bottom
			vertices[20].position = Vector3f(-0.5f, -0.5f, -0.5f);
			vertices[21].position = Vector3f(0.5f, -0.5f, -0.5f);
			vertices[22].position = Vector3f(0.5f, -0.5f, 0.5f);
			vertices[23].position = Vector3f(-0.5f, -0.5f, 0.5f);

			Blob blob(vertices.size() * sizeof(VertexPosition));
			blob.copyDataFrom(vertices.data());

			tmpVertexBuffer.init(&blob);

			m_pVertexArray = new VertexArray;
			m_pVertexArray->init(&tmpVertexBuffer, &VertexPosition::vertexBufferLayout);
		}

		{
			std::vector<unsigned int> indices
			{
				3,  1,  0,  3,  2,  1,
				7,  5,  4,  7,  6,  5,
				11, 9,  8,  11, 10, 9,
				15, 13, 12, 15, 14, 13,
				19, 17, 16, 19, 18, 17,
				23, 21, 20, 23, 22, 21
			};

			Blob blob(indices.size() * sizeof(unsigned int));
			blob.copyDataFrom(indices.data());

			m_pIndexBuffer = new IndexBuffer;
			m_pIndexBuffer->init(&blob);
		}

		{
			AssetLoader assetLoader;
			Blob* vsBlob = assetLoader.load("assets/shaders/Light.vert", AssetType::Shader);
			Blob* psBlob = assetLoader.load("assets/shaders/Light.frag", AssetType::Shader);

			m_pShader = new Shader;
			m_pShader->init(vsBlob, psBlob);

			SAFE_DELETE_SET_NULL(vsBlob);
			SAFE_DELETE_SET_NULL(psBlob);
		}
	}

	Light::~Light()
	{
		SAFE_DELETE_SET_NULL(m_pVertexArray);
		SAFE_DELETE_SET_NULL(m_pIndexBuffer);
		SAFE_DELETE_SET_NULL(m_pShader);
		SAFE_DELETE_SET_NULL(m_pCamera3D);
	}

	void Light::Draw()
	{
		if (m_pShader)
		{
			m_pShader->bind();
			glm::mat4 mvp{ 1.0f };
			mvp *= glm::perspective(m_pCamera3D->fov, m_pCamera3D->aspect, m_pCamera3D->nearZ, m_pCamera3D->farZ);
			mvp *= m_pCamera3D->m_transform.GetInverseWorldMatrix();
			mvp *= m_transform.GetWorldMatrix();
			m_pShader->setMat4("u_mvp", mvp, false);
		}
		if (m_pVertexArray)
			m_pVertexArray->bind();
		if (m_pIndexBuffer)
		{
			m_pIndexBuffer->bind();
			CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, m_pIndexBuffer->getCount(), GL_UNSIGNED_INT, (void*)0));
		}


		if (m_pShader)
			m_pShader->unbind();
		if (m_pVertexArray)
			m_pVertexArray->unbind();
		if (m_pIndexBuffer)
		{
			m_pIndexBuffer->unbind();
		}
	}
}