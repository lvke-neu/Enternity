#include "ModelBlobLoader.h"
#include "Engine/Blob.h"
#include "Engine/Log.h"
#include "ModelBlobHolder.h"
#include "Graphics/RHI/Mesh/MeshBlobHolder.h"
#include "Common/Macro.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/gtc/quaternion.hpp>

namespace Enternity
{
	ModelBlobLoader::ModelBlobLoader() : BlobLoader("model://")
	{

	}

	BlobHolder* ModelBlobLoader::createBlobHolder(const char* path)
	{
		return new ModelBlobHolder(this, path);
	}

	void ModelBlobLoader::doLoad(BlobHolder* blobHolder)
	{
		if (blobHolder->getLoadingState() != BlobHolder::loading_state_pending)
			return;

		ModelBlobHolder* modelBlobHolder = dynamic_cast<ModelBlobHolder*>(blobHolder);
		if (!modelBlobHolder)
			return;

		m_mtx.lock();

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(modelBlobHolder->getPath(), aiProcess_Triangulate | aiProcess_FlipUVs
			| aiProcess_GenNormals   | aiProcess_GenUVCoords | aiProcess_JoinIdenticalVertices);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			modelBlobHolder->loadFailed__();
			LOG_ERROR("ERROR::ASSIMP::{0}", importer.GetErrorString());
			m_mtx.unlock();
			return;
		}

		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];


			//mesh
			struct MeshData
			{
				std::vector<Vertex_Skeleton> vertices;
				std::vector<unsigned int> indices;
			};

			MeshData meshData;
			MeshBlobHolder::MeshDesc meshDesc;
			unsigned int offset = 0;

			for (unsigned int j = 0; j < mesh->mNumVertices; j++)
			{
				Vertex_Skeleton vertex;

				vertex.position.x = mesh->mVertices[j].x;
				vertex.position.y = mesh->mVertices[j].y;
				vertex.position.z = mesh->mVertices[j].z;

				vertex.normal.x = mesh->mNormals[j].x;
				vertex.normal.y = mesh->mNormals[j].y;
				vertex.normal.z = mesh->mNormals[j].z;

				if (mesh->HasTextureCoords(0))
				{
					vertex.texcoord.x = mesh->mTextureCoords[0][j].x;
					vertex.texcoord.y = -mesh->mTextureCoords[0][j].y + 1;
				}

				meshData.vertices.push_back(vertex);
			}

			meshDesc.vertexDataOffset = offset;
			meshDesc.vertexDataSize = (unsigned int)meshData.vertices.size() * sizeof(Vertex_Skeleton);
			offset += meshDesc.vertexDataSize;

			for (unsigned int j = 0; j < mesh->mNumFaces; j++)
			{
				for (unsigned int k = 0; k < mesh->mFaces[j].mNumIndices; k++)
				{
					meshData.indices.push_back(mesh->mFaces[j].mIndices[k]);
				}
			}

			meshDesc.indexDataOffset = offset;
			meshDesc.indexDataSize = (unsigned int)meshData.indices.size() * sizeof(unsigned int);
			offset += meshDesc.indexDataSize;

			MeshBlobHolder* meshBlobHolder = new MeshBlobHolder(nullptr, "");
			meshBlobHolder->m_layout = Vertex_Skeleton::s_layout;
			meshBlobHolder->m_meshDesc = meshDesc;

			Blob* blob = new Blob(offset);

			memcpy_s((char*)blob->getData() + meshDesc.vertexDataOffset,
				meshDesc.vertexDataSize,
				meshData.vertices.data(),
				meshDesc.vertexDataSize);
			memcpy_s((char*)blob->getData() + meshDesc.indexDataOffset,
				meshDesc.indexDataSize,
				meshData.indices.data(),
				meshDesc.indexDataSize);

			meshBlobHolder->loadSucceeded__(blob);
			SAFE_DELETE_SET_NULL(blob);

			modelBlobHolder->m_meshBlobHolders.push_back(meshBlobHolder);
		}

		modelBlobHolder->loadSucceeded__(nullptr);

		m_mtx.unlock();
	}
}