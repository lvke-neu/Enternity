#include "SkyboxObject.h"
#include "Core/Asset/AssetLoader.h"
#include "Core/Blob/Blob.h"
#include "Core/Log/Log.h"
#include "RHI/VertexBuffer.h"
#include "RHI/VertexArray.h"
#include "RHI/IndexBuffer.h"
#include "RHI/Shader.h"
#include "RHI/Texture.h"
#include "GUI/GUIRender.h"
#include "Utility/Utility.h"
#include "Vertex.h"
#include "Camera3D.h"
#include "Light.h"
#include <glad/glad.h>

#pragma warning(disable:4312) 

namespace Enternity
{
	SkyboxObject::SkyboxObject(Camera3D* camera3D)
	{
		m_pCamera3D = camera3D;

		{

			std::vector<Blob*> skyboxTextures;
			std::vector<std::string> path =
			{
				"right.jpg",
				"left.jpg",
				"top.jpg",
				"bottom.jpg",
				"front.jpg",
				"back.jpg"
			};

			AssetLoader assetLoader;
			for (int i = 0; i < 6; i++)
			{
				skyboxTextures.emplace_back(assetLoader.load(("assets/textures/skybox/default/" + path[i]).c_str(), AssetType::Texture, 0));
			}

			m_pTextureCube = new TextureCube;
			m_pTextureCube->init(skyboxTextures);
			for (int i = 0; i < 6; i++)
			{
				SAFE_DELETE_SET_NULL(skyboxTextures[i]);
			}
		}


		{
			VertexBuffer tmpVertexBuffer;
			std::vector<VertexPosNormalTexcoord> vertices;
			vertices.resize(24);

			//front
			vertices[0].position = Vector3f(-1.0f, 1.0f, 1.0f);
			vertices[1].position = Vector3f(1.0f, 1.0f, 1.0f);
			vertices[2].position = Vector3f(1.0f, -1.0f, 1.0f);
			vertices[3].position = Vector3f(-1.0f, -1.0f, 1.0f);

			//back
			vertices[4].position = Vector3f(-1.0f, 1.0f, -1.0f);
			vertices[5].position = Vector3f(1.0f, 1.0f, -1.0f);
			vertices[6].position = Vector3f(1.0f, -1.0f, -1.0f);
			vertices[7].position = Vector3f(-1.0f, -1.0f, -1.0f);

			//left
			vertices[8].position = Vector3f(-1.0f, 1.0f, -1.0f);
			vertices[9].position = Vector3f(-1.0f, 1.0f, 1.0f);
			vertices[10].position = Vector3f(-1.0f, -1.0f, 1.0f);
			vertices[11].position = Vector3f(-1.0f, -1.0f, -1.0f);

			//right
			vertices[12].position = Vector3f(1.0f, 1.0f, -1.0f);
			vertices[13].position = Vector3f(1.0f, 1.0f, 1.0f);
			vertices[14].position = Vector3f(1.0f, -1.0f, 1.0f);
			vertices[15].position = Vector3f(1.0f, -1.0f, -1.0f);

			//top
			vertices[16].position = Vector3f(-1.0f, 1.0f, -1.0f);
			vertices[17].position = Vector3f(1.0f, 1.0f, -1.0f);
			vertices[18].position = Vector3f(1.0f, 1.0f, 1.0f);
			vertices[19].position = Vector3f(-1.0f, 1.0f, 1.0f);

			//bottom
			vertices[20].position = Vector3f(-1.0f, -1.0f, -1.0f);
			vertices[21].position = Vector3f(1.0f, -1.0f, -1.0f);
			vertices[22].position = Vector3f(1.0f, -1.0f, 1.0f);
			vertices[23].position = Vector3f(-1.0f, -1.0f, 1.0f);

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
			Blob* vsBlob = assetLoader.load("assets/shaders/Skybox.vert", AssetType::Shader);
			Blob* psBlob = assetLoader.load("assets/shaders/Skybox.frag", AssetType::Shader);

			m_pShader = new Shader;
			m_pShader->init(vsBlob, psBlob);

			SAFE_DELETE_SET_NULL(vsBlob);
			SAFE_DELETE_SET_NULL(psBlob);
		}

	}

	SkyboxObject::~SkyboxObject()
	{
		SAFE_DELETE_SET_NULL(m_pVertexArray);
		SAFE_DELETE_SET_NULL(m_pIndexBuffer);
		SAFE_DELETE_SET_NULL(m_pShader);
		SAFE_DELETE_SET_NULL(m_pTextureCube);
	}

	void SkyboxObject::Draw()
	{
		glDepthFunc(GL_LEQUAL);
		if (m_pShader)
		{
			m_pShader->bind();

			m_pShader->setMat4("u_view", glm::mat4(glm::mat3(m_pCamera3D->m_transform.GetInverseWorldMatrix())), false);
			m_pShader->setMat4("u_proj", glm::perspective(m_pCamera3D->fov, m_pCamera3D->aspect, m_pCamera3D->nearZ, m_pCamera3D->farZ), false);
		}

		if (m_pTextureCube)
			m_pTextureCube->bind(0);

		if (m_pVertexArray)
			m_pVertexArray->bind();
		if (m_pIndexBuffer)
		{
			m_pIndexBuffer->bind();
			CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, m_pIndexBuffer->getCount(), GL_UNSIGNED_INT, (void*)0));
		}


		if (m_pShader)
			m_pShader->unbind();
		if (m_pTextureCube)
			m_pTextureCube->unbind();
		if (m_pVertexArray)
			m_pVertexArray->unbind();
		if (m_pIndexBuffer)
		{
			m_pIndexBuffer->unbind();
		}
		glDepthFunc(GL_LESS);
	}

	void SkyboxObject::RecompileShader()
	{
		//SAFE_DELETE_SET_NULL(m_pShader);

		//AssetLoader assetLoader;
		//Blob* vsBlob = assetLoader.load("assets/shaders/PhongScene.vert", AssetType::Shader);
		//Blob* psBlob = assetLoader.load("assets/shaders/PhongScene.frag", AssetType::Shader);

		//m_pShader = new Shader;
		//m_pShader->init(vsBlob, psBlob);

		//SAFE_DELETE_SET_NULL(vsBlob);
		//SAFE_DELETE_SET_NULL(psBlob);
	}

	void SkyboxObject::RenderGUI()
	{
		//ImGui::DragFloat3("transaltion", &m_transform.m_Translation[0], 0.1f);
		//ImGui::DragFloat3("rotation", &m_transform.m_Rotation[0], 0.1f);
		//ImGui::DragFloat3("scale", &m_transform.m_Scale[0], 0.1f);
		//ImGui::Separator();
		//ImGui::Image((void*)m_material.ambient->getRenderId(), ImVec2(50, 50), { 0, 1 }, { 1, 0 });
		//ImGui::Image((void*)m_material.diffuse->getRenderId(), ImVec2(50, 50), { 0, 1 }, { 1, 0 });
		//ImGui::Image((void*)m_material.specular->getRenderId(), ImVec2(50, 50), { 0, 1 }, { 1, 0 });
		//ImGui::DragFloat("shininess", &m_material.shininess, 1.0f);
	}

}