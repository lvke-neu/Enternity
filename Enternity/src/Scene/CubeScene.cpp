#include "CubeScene.h"
#include "Core/Reflection/Reflection.h"
#include "Core/Blob/Blob.h"
#include "Core/Asset/AssetLoader.h"
#include "Core/Log/Log.h"
#include "Common/Vertex.h"
#include "Common/Camera3D.h"
#include "Common/CameraController.h"
#include "RHI/VertexBuffer.h"
#include "RHI/VertexArray.h"
#include "RHI/IndexBuffer.h"
#include "RHI/Shader.h"
#include "RHI/Texture.h"
#include "Utility/Utility.h"
#include "GUI/GUIRender.h"
#include <glad/glad.h>

namespace Enternity
{
	REGISTER_CLASS(IScene, "CubeScene", CubeScene);

	void CubeScene::Initialize()
	{
		if (m_bIsInit)
			return;

		m_pCamera3D = new Camera3D;
		m_pCameraController = new CameraController(m_pCamera3D);

		m_transform.m_Scale = glm::vec3(1, 1, 0);
		m_transform.m_Translation = glm::vec3(0, 0, 2);

		{
			VertexBuffer tmpVertexBuffer;
			std::vector<VertexPosNormalTexcoord> vertices;
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
			vertices[7].position = Vector3f(-0.5f, -0.5f,-0.5f);

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

			for (int i = 0; i < 4; i++)
			{
				vertices[i].normal = Vector3f(0.0f, 0.0f, 1.0f);
				vertices[i + 4].normal = Vector3f(0.0f, 0.0f, -1.0f);

				vertices[i + 8].normal = Vector3f(-1.0f, 0.0f, 0.0f);
				vertices[i + 12].normal = Vector3f(1.0f, 0.0f, 0.0f);

				vertices[i + 16].normal = Vector3f(0.0f, 1.0f, 0.0f);
				vertices[i + 20].normal = Vector3f(0.0f, -1.0f, 0.0f);
			}

			for (int i = 0; i < 6; ++i)
			{
				vertices[i * 4].texcoord = Vector2f(0.0f, 1.0f);
				vertices[i * 4 + 1].texcoord = Vector2f(1.0f, 1.0f);
				vertices[i * 4 + 2].texcoord = Vector2f(1.0f, 0.0f);
				vertices[i * 4 + 3].texcoord = Vector2f(0.0f, 0.0f);
			}

			Blob blob(vertices.size() * sizeof(VertexPosNormalTexcoord));
			blob.copyDataFrom(vertices.data());

			tmpVertexBuffer.init(&blob);

			m_pVertexArray = new VertexArray;
			m_pVertexArray->init(&tmpVertexBuffer, &VertexPosNormalTexcoord::vertexBufferLayout);
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
			Blob* vsBlob = assetLoader.load("assets/shaders/CubeScene.vert", AssetType::Shader);
			Blob* psBlob = assetLoader.load("assets/shaders/CubeScene.frag", AssetType::Shader);

			m_pShader = new Shader;
			m_pShader->init(vsBlob, psBlob);

			SAFE_DELETE_SET_NULL(vsBlob);
			SAFE_DELETE_SET_NULL(psBlob);
		}

		{
			AssetLoader assetLoader;
			TextureBlob* texBlob = (TextureBlob*)assetLoader.load("assets/textures/blending_transparent_window.png", AssetType::Texture);

			m_pTexture = new Texture2D;
			m_pTexture->init(texBlob);

			SAFE_DELETE_SET_NULL(texBlob);


			texBlob = (TextureBlob*)assetLoader.load("assets/textures/box_ambient.png", AssetType::Texture);

			m_pTexture2 = new Texture2D;
			m_pTexture2->init(texBlob);
			SAFE_DELETE_SET_NULL(texBlob);
		}

		m_bIsInit = true;
	}

	void CubeScene::Finalize()
	{
		SAFE_DELETE_SET_NULL(m_pVertexArray);
		SAFE_DELETE_SET_NULL(m_pIndexBuffer);
		SAFE_DELETE_SET_NULL(m_pShader);
		SAFE_DELETE_SET_NULL(m_pCamera3D);
		SAFE_DELETE_SET_NULL(m_pCameraController);
	}

	void CubeScene::Tick(float deltaTime)
	{


	

		if (m_pShader)
		{
			m_pShader->bind();
			glm::mat4 mvp{ 1.0f };
			mvp *= glm::perspective(m_pCamera3D->fov, m_pCamera3D->aspect, m_pCamera3D->nearZ, m_pCamera3D->farZ);
			mvp *= m_pCamera3D->m_transform.GetInverseWorldMatrix();
			mvp *= m_transform2.GetWorldMatrix();
			m_pShader->setMat4("u_mvp", mvp, false);
		}

		if (m_pTexture2)
			m_pTexture2->bind(0);
		if (m_pVertexArray)
			m_pVertexArray->bind();
		if (m_pIndexBuffer)
		{
			m_pIndexBuffer->bind();
			CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, m_pIndexBuffer->getCount(), GL_UNSIGNED_INT, (void*)0));
		}


		if (m_pShader)
			m_pShader->unbind();
		if (m_pTexture2)
			m_pTexture2->unbind();
		if (m_pVertexArray)
			m_pVertexArray->unbind();
		if (m_pIndexBuffer)
		{
			m_pIndexBuffer->unbind();
		}


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if (m_pShader)
		{
			m_pShader->bind();
			glm::mat4 mvp{ 1.0f };
			mvp *= glm::perspective(m_pCamera3D->fov, m_pCamera3D->aspect, m_pCamera3D->nearZ, m_pCamera3D->farZ);
			mvp *= m_pCamera3D->m_transform.GetInverseWorldMatrix();
			mvp *= m_transform.GetWorldMatrix();
			m_pShader->setMat4("u_mvp", mvp, false);
		}

		if (m_pTexture)
			m_pTexture->bind(0);
		if (m_pVertexArray)
			m_pVertexArray->bind();
		if (m_pIndexBuffer)
		{
			m_pIndexBuffer->bind();
			CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, m_pIndexBuffer->getCount(), GL_UNSIGNED_INT, (void*)0));
		}


		if (m_pShader)
			m_pShader->unbind();
		if (m_pTexture)
			m_pTexture->unbind();
		if (m_pVertexArray)
			m_pVertexArray->unbind();
		if (m_pIndexBuffer)
		{
			m_pIndexBuffer->unbind();
		}
		glDisable(GL_BLEND);
	}

	void CubeScene::RecompileShader()
	{
		SAFE_DELETE_SET_NULL(m_pShader);

		AssetLoader assetLoader;
		Blob* vsBlob = assetLoader.load("assets/shaders/CubeScene.vert", AssetType::Shader);
		Blob* psBlob = assetLoader.load("assets/shaders/CubeScene.frag", AssetType::Shader);

		m_pShader = new Shader;
		m_pShader->init(vsBlob, psBlob);

		SAFE_DELETE_SET_NULL(vsBlob);
		SAFE_DELETE_SET_NULL(psBlob);
	}

	void CubeScene::RenderGUI()
	{
		ImGui::Begin("CubeScene");


		ImGui::DragFloat3("transaltion", &m_transform.m_Translation[0], 0.1f);
		ImGui::DragFloat3("rotation", &m_transform.m_Rotation[0], 1);
		ImGui::DragFloat3("scale", &m_transform.m_Scale[0], 0.1f);

		ImGui::DragFloat3("camtransaltion", &m_pCamera3D->m_transform.m_Translation[0], 0.1f);
		ImGui::DragFloat3("camrotation", &m_pCamera3D->m_transform.m_Rotation[0], 1);

		if(ImGui::Button("Reset Camera"))
		{
			m_pCamera3D->m_transform.m_Translation = { 0.0f };
			m_pCamera3D->m_transform.m_Rotation = { 0.0f };
		}

		ImGui::End();
	}

	void CubeScene::OnResize(int width, int height)
	{
		m_pCamera3D->aspect = static_cast<float>(width) / height;
	}
}