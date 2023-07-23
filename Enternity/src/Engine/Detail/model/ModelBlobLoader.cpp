#include "ModelBlobLoader.h"
#include "Engine/Blob.h"
#include "Engine/Log.h"
#include "ModelBlobHolder.h"
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

	BlobHolder* ModelBlobLoader::createBlobHolder(const std::string& path)
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

		assimpLoad(blobHolder);
	}

	void ModelBlobLoader::assimpLoad(BlobHolder* blobHolder)
	{
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

		struct Mesh
		{
			std::vector<Vertex_Positon_Normal_Texcoord> vertices;
			std::vector<unsigned int> indices;
		};

		std::vector<Mesh> meshes;
		ModelBlobHolder* modelBlobHolder = dynamic_cast<ModelBlobHolder*>(blobHolder);

		unsigned int offset = 0;
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			Mesh mesh;
			ModelBlobHolder::SubMeshDesc subMeshDesc;

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

				mesh.vertices.push_back(vertex);
			}

			subMeshDesc.vertexDataOffset = offset;
			subMeshDesc.vertexDataSize = (unsigned int)mesh.vertices.size() * sizeof(Vertex_Positon_Normal_Texcoord);
			offset += subMeshDesc.vertexDataSize;

			for (unsigned int j = 0; j < assimpMesh->mNumFaces; j++)
			{
				for (unsigned int k = 0; k < assimpMesh->mFaces[j].mNumIndices; k++)
				{
					mesh.indices.push_back(assimpMesh->mFaces[j].mIndices[k]);
				}
			}

			subMeshDesc.indexDataOffset = offset;
			subMeshDesc.indexDataSize = (unsigned int)mesh.indices.size() * sizeof(unsigned int);
			offset += subMeshDesc.indexDataSize;

			meshes.push_back(mesh);
			modelBlobHolder->m_subMeshDescs.push_back(subMeshDesc);
		}

		Blob* blob = new Blob(offset);
		for (int i = 0; i < modelBlobHolder->m_subMeshDescs.size(); ++i)
		{
			memcpy_s((char*)blob->getData() + modelBlobHolder->m_subMeshDescs[i].vertexDataOffset,
				modelBlobHolder->m_subMeshDescs[i].vertexDataSize,
				meshes[i].vertices.data(), 
				modelBlobHolder->m_subMeshDescs[i].vertexDataSize);

			memcpy_s((char*)blob->getData() + modelBlobHolder->m_subMeshDescs[i].indexDataOffset,
				modelBlobHolder->m_subMeshDescs[i].indexDataSize,
				meshes[i].indices.data(),
				modelBlobHolder->m_subMeshDescs[i].indexDataSize);
		}
		
		modelBlobHolder->loadSucceeded__(blob);
		SAFE_DELETE_SET_NULL(blob);

		m_mtx.unlock();
	}
}