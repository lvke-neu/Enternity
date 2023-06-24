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

				vertex.normal.x = assimpMesh->mNormals[i].x;
				vertex.normal.y = assimpMesh->mNormals[i].y;
				vertex.normal.z = assimpMesh->mNormals[i].z;

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
}