#include "MeshBlobLoader.h"
#include "Engine/Blob.h"
#include "Engine/BlobHolder.h"
#include "Engine/Log.h"
#include "MeshBlobHolder.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

namespace Enternity
{
	MeshBlobLoader::MeshBlobLoader() : BlobLoader("mesh://")
	{

	}

	BlobHolder* MeshBlobLoader::createBlobHolder(const std::string& path)
	{
		return new MeshBlobHolder(this, path);
	}

	void MeshBlobLoader::doLoad(BlobHolder* blobHolder)
	{
		if (blobHolder->getLoadingState() != BlobHolder::loading_state_pending)
			return;

		MeshBlobHolder* meshBlobHolder = dynamic_cast<MeshBlobHolder*>(blobHolder);
		if (!meshBlobHolder)
			return;

		assimpLoad(blobHolder);
	}

	void MeshBlobLoader::assimpLoad(BlobHolder* blobHolder)
	{
		m_mtx.lock();

		/*Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(blobHolder->getPath(), aiProcess_Triangulate | aiProcess_FlipUVs
			| aiProcess_GenNormals | aiProcess_GenBoundingBoxes | aiProcess_GenUVCoords | aiProcess_JoinIdenticalVertices);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG_ERROR("ERROR::ASSIMP::{0}", importer.GetErrorString());
			blobHolder->loadFailed__();
			m_mtx.unlock();
			return;
		}

		struct Vertex_Positon_Normal_Texcoord
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 texcoord;
		};


		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			std::vector<Vertex_Positon_Normal_Texcoord> vertex;
			std::vector<unsigned int> index;

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

			vertices.push_back(vertices);
			indices.push_back(indices);
		}

		m_state = Asset2::LoadingState::loading_state_succeeded;*/

		m_mtx.unlock();
	}
}