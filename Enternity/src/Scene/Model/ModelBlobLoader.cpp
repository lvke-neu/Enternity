#include "ModelBlobLoader.h"
#include "Engine/Blob.h"
#include "Engine/Log.h"
#include "ModelBlobHolder.h"
#include "Graphics/RHI/Mesh/MeshBlobHolder.h"
#include "Graphics/RHI/Mesh/VertexDefine.h"
#include "Common/Macro.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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
		const aiScene* scene = importer.ReadFile(blobHolder->getPath(), aiProcess_Triangulate | aiProcess_FlipUVs
			| aiProcess_GenNormals | aiProcess_GenBoundingBoxes | aiProcess_GenUVCoords | aiProcess_JoinIdenticalVertices);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			blobHolder->loadFailed__();
			LOG_ERROR("ERROR::ASSIMP::{0}", importer.GetErrorString());
			m_mtx.unlock();
			return;
		}

		struct MeshData
		{
			std::vector<Vertex_Positon_Normal_Texcoord> vertices;
			std::vector<unsigned int> indices;
		};

		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			MeshData meshData;
			MeshBlobHolder::MeshDesc meshDesc;
			unsigned int offset = 0;

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

				meshData.vertices.push_back(vertex);
			}

			meshDesc.vertexDataOffset = offset;
			meshDesc.vertexDataSize = (unsigned int)meshData.vertices.size() * sizeof(Vertex_Positon_Normal_Texcoord);
			offset += meshDesc.vertexDataSize;

			for (unsigned int j = 0; j < assimpMesh->mNumFaces; j++)
			{
				for (unsigned int k = 0; k < assimpMesh->mFaces[j].mNumIndices; k++)
				{
					meshData.indices.push_back(assimpMesh->mFaces[j].mIndices[k]);
				}
			}

			meshDesc.indexDataOffset = offset;
			meshDesc.indexDataSize = (unsigned int)meshData.indices.size() * sizeof(unsigned int);
			offset += meshDesc.indexDataSize;

			MeshBlobHolder* meshBlobHolder = new MeshBlobHolder(nullptr, "");
			meshBlobHolder->m_layout = Vertex_Positon_Normal_Texcoord::s_layout;
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


			aiMaterial* material = scene->mMaterials[assimpMesh->mMaterialIndex];
			aiString str;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
			int j = 0;
		}
		modelBlobHolder->loadSucceeded__(nullptr);
		m_mtx.unlock();
	}
}