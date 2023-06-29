#include "MeshAsset.h"
#include "Engine/Log.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Enternity
{
	MeshAsset::MeshAsset(const std::string& fullPath) :
		m_fullPath(fullPath)
	{

	}

	MeshAsset::~MeshAsset()
	{

	}

	void MeshAsset::doLoad()
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(m_fullPath, aiProcess_Triangulate | aiProcess_FlipUVs
			| aiProcess_GenNormals | aiProcess_GenBoundingBoxes | aiProcess_GenUVCoords | aiProcess_JoinIdenticalVertices);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG_ERROR("ERROR::ASSIMP::{0}", importer.GetErrorString());
			m_state = Asset::loading_state_failed;
			return;
		}

		m_vertices.clear();
		m_indices.clear();
		
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			std::vector<Vertex_Positon_Normal_Texcoord> vertices;
			std::vector<unsigned int> indices;

			aiMesh* assimpMesh = scene->mMeshes[i];
			for (unsigned int j = 0; j < assimpMesh->mNumVertices; j++)
			{
				Vertex_Positon_Normal_Texcoord vertex;
				vertex.position.x = assimpMesh->mVertices[j].x;
				vertex.position.y = assimpMesh->mVertices[j].y;
				vertex.position.z = assimpMesh->mVertices[j].z;

				vertex.normal.x = assimpMesh->mNormals[j].x;
				vertex.normal.y = assimpMesh->mNormals[j].y;
				vertex.normal.z = assimpMesh->mNormals[j].z;

				if (assimpMesh->HasTextureCoords(0))
				{
					vertex.texcoord.x = assimpMesh->mTextureCoords[0][j].x;
					vertex.texcoord.y = -assimpMesh->mTextureCoords[0][j].y + 1;
				}

				vertices.push_back(vertex);
			}

			for (unsigned int j = 0; j < assimpMesh->mNumFaces; j++)
			{
				for (unsigned int k = 0; k < assimpMesh->mFaces[j].mNumIndices; k++)
				{
					indices.push_back(assimpMesh->mFaces[j].mIndices[k]);
				}
			}
	
			aiMaterial* material = scene->mMaterials[assimpMesh->mMaterialIndex];
			aiString textureFilepath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilepath);

			//if (std::string(textureFilepath.C_Str()) == "")
			//{
			//	m_materials.push_back("assets/textures/white_background.jpeg");
			//}
			//else
			//{
			//	m_materials.push_back(m_fullPath.substr(0, m_fullPath.find_last_of('/')) + "/" + textureFilepath.C_Str());
			//}
			m_materials.push_back(m_fullPath.substr(0, m_fullPath.find_last_of('/')) + "/" + textureFilepath.C_Str());
			m_vertices.push_back(vertices);
			m_indices.push_back(indices);
		}

		m_state = Asset::loading_state_succeeded;
	}



	QuadMeshAsset::QuadMeshAsset() : MeshAsset("BasicPrimitive::Quad")
	{
		m_materials.resize(1);
	}

	QuadMeshAsset::~QuadMeshAsset()
	{

	}

	void QuadMeshAsset::doLoad()
	{
		m_vertices.resize(1);
		m_indices.resize(1);

		m_vertices[0].resize(4);
		m_vertices[0][0].position = glm::vec3(-1, 1, 0);
		m_vertices[0][1].position = glm::vec3(1, 1, 0);
		m_vertices[0][2].position = glm::vec3(1, -1, 0);
		m_vertices[0][3].position = glm::vec3(-1, -1, 0);

		m_vertices[0][0].texcoord = glm::vec2(0, 1);
		m_vertices[0][1].texcoord = glm::vec2(1, 1);
		m_vertices[0][2].texcoord = glm::vec2(1, 0);
		m_vertices[0][3].texcoord = glm::vec2(0, 0);

		m_indices[0] = { 0, 3, 2, 0, 2, 1 };

		m_state = Asset::loading_state_succeeded;
	}


	BoxMeshAsset::BoxMeshAsset() : MeshAsset("BasicPrimitive::Box")
	{
		m_materials.resize(1);
	}

	BoxMeshAsset::~BoxMeshAsset()
	{

	}

	void BoxMeshAsset::doLoad()
	{
		m_vertices.resize(1);
		m_indices.resize(1);

		m_vertices[0].resize(24);
		m_vertices[0][0].position = glm::vec3(1, -1, 1);
		m_vertices[0][1].position = glm::vec3(1, 1, 1);
		m_vertices[0][2].position = glm::vec3(1, 1, -1);
		m_vertices[0][3].position = glm::vec3(1, -1, -1);

		m_vertices[0][4].position = glm::vec3(-1, -1, -1);
		m_vertices[0][5].position = glm::vec3(-1, 1, -1);
		m_vertices[0][6].position = glm::vec3(-1, 1, 1);
		m_vertices[0][7].position = glm::vec3(-1, -1, 1);

		m_vertices[0][8].position = glm::vec3(-1, 1, 1);
		m_vertices[0][9].position = glm::vec3(-1, 1, -1);
		m_vertices[0][10].position = glm::vec3(1, 1, -1);
		m_vertices[0][11].position = glm::vec3(1, 1, 1);

		m_vertices[0][12].position = glm::vec3(1, -1, 1);
		m_vertices[0][13].position = glm::vec3(1, -1, -1);
		m_vertices[0][14].position = glm::vec3(-1, -1, -1);
		m_vertices[0][15].position = glm::vec3(-1, -1, 1);

		m_vertices[0][16].position = glm::vec3(1, -1, -1);
		m_vertices[0][17].position = glm::vec3(1, 1, -1);
		m_vertices[0][18].position = glm::vec3(-1, 1, -1);
		m_vertices[0][19].position = glm::vec3(-1, -1, -1);

		m_vertices[0][20].position = glm::vec3(-1, -1, 1);
		m_vertices[0][21].position = glm::vec3(-1, 1, 1);
		m_vertices[0][22].position = glm::vec3(1, 1, 1);
		m_vertices[0][23].position = glm::vec3(1, -1, 1);

		m_indices[0] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4,
			8, 9, 10, 10, 11, 8,
			12, 13, 14, 14, 15, 12,
			16, 17, 18, 18, 19, 16,
			20, 21, 22, 22, 23, 20
		};

		m_state = Asset::loading_state_succeeded;
	}
}