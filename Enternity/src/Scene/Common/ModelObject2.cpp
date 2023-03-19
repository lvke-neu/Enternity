#include "ModelObject2.h"
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
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glad/glad.h>

namespace Enternity
{

	ModelObject2::ModelObject2(Camera3D* camera3D, Light* light)
	{
		m_pCamera3D = camera3D;
		m_pLight = light;
	}

	ModelObject2::~ModelObject2()
	{
		for (int i = 0; i < m_pShaders.size(); i++)
		{
			SAFE_DELETE_SET_NULL(m_pVertexArraies[i]);
			SAFE_DELETE_SET_NULL(m_pIndexBuffers[i]);
			SAFE_DELETE_SET_NULL(m_pShaders[i]);
		}
	}

	void ModelObject2::Load(const std::string& path)
	{
		if (m_bIsLoad)
			return;

		m_modelFilePath = path;

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(m_modelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs
			| aiProcess_GenNormals | aiProcess_GenBoundingBoxes | aiProcess_GenUVCoords);


		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG_ERROR("ERROR::ASSIMP::" + importer.GetErrorString());
			return;
		}

		ProcessNode(scene->mRootNode, scene);

		m_bIsLoad = true;
	}

	void ModelObject2::Draw()
	{
		for (int i = 0; i < m_pShaders.size(); i++)
		{

				m_pShaders[i]->bind();
				m_pShaders[i]->setMat4("u_model", m_transform.GetWorldMatrix(), false);
				m_pShaders[i]->setMat4("u_view", m_pCamera3D->m_transform.GetInverseWorldMatrix(), false);
				m_pShaders[i]->setMat4("u_proj", glm::perspective(m_pCamera3D->fov, m_pCamera3D->aspect, m_pCamera3D->nearZ, m_pCamera3D->farZ), false);
				m_pShaders[i]->setFloat3("u_lightPos", m_pLight->m_transform.m_Translation);
				m_pShaders[i]->setFloat3("u_viewPos", m_pCamera3D->m_transform.m_Translation);


				m_pShaders[i]->setFloat1("u_material.shininess", m_materials[i].shininess);
				m_materials[i].ambient->bind(0);
				m_materials[i].diffuse->bind(1);
				m_materials[i].specular->bind(2);

				m_pVertexArraies[i]->bind();
				m_pIndexBuffers[i]->bind();
				CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, m_pIndexBuffers[i]->getCount(), GL_UNSIGNED_INT, (void*)0));

				m_pShaders[i]->unbind();
				m_materials[i].ambient->unbind();
				m_materials[i].diffuse->unbind();
				m_materials[i].specular->unbind();
				m_pVertexArraies[i]->unbind();
				m_pIndexBuffers[i]->unbind();
		}
	}

	void ModelObject2::RenderGUI()
	{
		ImGui::PushID("ModelObject2");
		ImGui::DragFloat3("transaltion", &m_transform.m_Translation[0], 0.1f);
		ImGui::DragFloat3("rotation", &m_transform.m_Rotation[0], 0.1f);
		ImGui::DragFloat3("scale", &m_transform.m_Scale[0], 0.1f);
		ImGui::PopID();
	}

	void ModelObject2::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			ProcessMesh(mesh, scene);
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	void ModelObject2::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{

		{
			AssetLoader assetLoader;
			Blob* vsBlob = assetLoader.load("assets/shaders/PhongScene.vert", AssetType::Shader);
			Blob* psBlob = assetLoader.load("assets/shaders/SimpleColor.frag", AssetType::Shader);

			m_pShaders.emplace_back( new Shader);
			m_pShaders.back()->init(vsBlob, psBlob);

			SAFE_DELETE_SET_NULL(vsBlob);
			SAFE_DELETE_SET_NULL(psBlob);
		}

		{
			VertexBuffer tmpVertexBuffer;
			std::vector<VertexPosNormalTexcoord> vertices;
			vertices.resize(mesh->mNumVertices);
			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				//position
				vertices[i].position.x = mesh->mVertices[i].x;
				vertices[i].position.y = mesh->mVertices[i].y;
				vertices[i].position.z = mesh->mVertices[i].z;

				//normal
				vertices[i].normal.x = mesh->mNormals[i].x;
				vertices[i].normal.y = mesh->mNormals[i].y;
				vertices[i].normal.z = mesh->mNormals[i].z;

				//texcoord
				if (mesh->HasTextureCoords(0))
				{
					vertices[i].texcoord.x = mesh->mTextureCoords[0][i].x;
					vertices[i].texcoord.y = -mesh->mTextureCoords[0][i].y + 1;
				}
			}

			Blob blob(vertices.size() * sizeof(VertexPosNormalTexcoord));
			blob.copyDataFrom(vertices.data());

			tmpVertexBuffer.init(&blob);

			m_pVertexArraies.emplace_back(new VertexArray);
			m_pVertexArraies.back()->init(&tmpVertexBuffer, &VertexPosNormalTexcoord::vertexBufferLayout);
		}
	
		{
			//index
			std::vector<unsigned int> indices;
			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
				{
					indices.push_back(mesh->mFaces[i].mIndices[j]);
				}
			}

			Blob blob(indices.size() * sizeof(unsigned int));
			blob.copyDataFrom(indices.data());

			m_pIndexBuffers.emplace_back(new IndexBuffer);
			m_pIndexBuffers.back()->init(&blob);
		}

		{

			//material
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			aiString ambientTexture;
			aiString diffuseTexture;
			aiString specularTexture;

			material->GetTexture(aiTextureType_AMBIENT, 0, &ambientTexture);
			material->GetTexture(aiTextureType_DIFFUSE, 0, &diffuseTexture);
			material->GetTexture(aiTextureType_SPECULAR, 0, &specularTexture);

			std::string ambientTextureFilePath;
			std::string diffuseTextureFilePath;
			std::string specularTextureFilePath;

			ambientTextureFilePath = std::string(ambientTexture.C_Str()) == "" ? "assets/textures/white_background.jpeg" : m_modelFilePath.substr(0, m_modelFilePath.find_last_of('/')) + "/" + ambientTexture.C_Str();
			diffuseTextureFilePath = std::string(diffuseTexture.C_Str()) == "" ? "assets/textures/white_background.jpeg" : m_modelFilePath.substr(0, m_modelFilePath.find_last_of('/')) + "/" + diffuseTexture.C_Str();
			specularTextureFilePath = std::string(specularTexture.C_Str()) == "" ? "assets/textures/white_background.jpeg" : m_modelFilePath.substr(0, m_modelFilePath.find_last_of('/')) + "/" + specularTexture.C_Str();

			AssetLoader assetLoader;
			TextureBlob* texBlob = (TextureBlob*)assetLoader.load(diffuseTextureFilePath.c_str(), AssetType::Texture);

			Texture2D* pAmbientTexture = new Texture2D;
			pAmbientTexture->init(texBlob);
			SAFE_DELETE_SET_NULL(texBlob);

			texBlob = (TextureBlob*)assetLoader.load(diffuseTextureFilePath.c_str(), AssetType::Texture);
			Texture2D* pDiffuseTexture = new Texture2D;
			pDiffuseTexture->init(texBlob);
			SAFE_DELETE_SET_NULL(texBlob);

			texBlob = (TextureBlob*)assetLoader.load(specularTextureFilePath.c_str(), AssetType::Texture);
			Texture2D* pSpecularTexture = new Texture2D;
			pSpecularTexture->init(texBlob);
			SAFE_DELETE_SET_NULL(texBlob);

			m_materials.emplace_back(PhongMaterial{ pAmbientTexture, pDiffuseTexture, pSpecularTexture, 32.0f });
		}
	}

}