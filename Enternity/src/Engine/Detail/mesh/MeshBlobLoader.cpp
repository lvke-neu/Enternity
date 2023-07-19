#include "MeshBlobLoader.h"
#include "Engine/Blob.h"
#include "Engine/BlobHolder.h"
#include "Engine/Log.h"
#include "MeshBlobHolder.h"
#include "Graphics/RHI/Mesh/VertexDefine.h"
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
		MeshBlobHolder* meshBlobHolder = dynamic_cast<MeshBlobHolder*>(blobHolder);

		unsigned int offset = 0;
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			Mesh mesh;
			MeshBlobHolder::SubMeshDesc subMeshDesc;

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
			meshBlobHolder->m_subMeshDescs.push_back(subMeshDesc);
		}

		Blob* blob = new Blob(offset);
		for (int i = 0; i < meshBlobHolder->m_subMeshDescs.size(); ++i)
		{
			memcpy_s((char*)blob->getData() + meshBlobHolder->m_subMeshDescs[i].vertexDataOffset, 
				meshBlobHolder->m_subMeshDescs[i].vertexDataSize,
				meshes[i].vertices.data(), 
				meshBlobHolder->m_subMeshDescs[i].vertexDataSize);

			memcpy_s((char*)blob->getData() + meshBlobHolder->m_subMeshDescs[i].indexDataOffset,
				meshBlobHolder->m_subMeshDescs[i].indexDataSize,
				meshes[i].indices.data(),
				meshBlobHolder->m_subMeshDescs[i].indexDataSize);
		}
		
		meshBlobHolder->loadSucceeded__(blob);
		SAFE_DELETE_SET_NULL(blob);

		m_mtx.unlock();
	}


	//void MeshBlobLoader::assimpLoad(BlobHolder* blobHolder)
	//{
	//	m_mtx.lock();

	//	Assimp::Importer importer;
	//	const aiScene* scene = importer.ReadFile(blobHolder->getPath(), aiProcess_Triangulate | aiProcess_FlipUVs
	//		| aiProcess_GenNormals | aiProcess_GenBoundingBoxes | aiProcess_GenUVCoords | aiProcess_JoinIdenticalVertices);

	//	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	//	{
	//		blobHolder->loadFailed__();
	//		LOG_ERROR("ERROR::ASSIMP::{0}", importer.GetErrorString());
	//		m_mtx.unlock();
	//		return;
	//	}

	//	struct Vertex_Positon_Normal_Texcoord
	//	{
	//		glm::vec3 position;
	//		glm::vec3 normal;
	//		glm::vec2 texcoord;
	//	};

	//	struct Mesh
	//	{
	//		std::vector<Vertex_Positon_Normal_Texcoord> vertices;
	//		std::vector<unsigned int> indices;
	//	};

	//	std::vector<Mesh> meshes;
	//	MeshBlobHolder* meshBlobHolder = dynamic_cast<MeshBlobHolder*>(blobHolder);
	//	
	//	Mesh mesh;
	//	mesh.vertices.push_back({ {1,2,3} , {4,5,6} ,{7,8} });
	//	mesh.indices = { 9,10,11 };
	//	meshes.push_back(mesh);
	//	MeshBlobHolder::SubMeshDesc subMeshDesc;
	//	subMeshDesc.vertexDataOffset = 0;
	//	subMeshDesc.vertexDataSize = mesh.vertices.size() * sizeof(Vertex_Positon_Normal_Texcoord);
	//	subMeshDesc.indexDataOffset = mesh.vertices.size() * sizeof(Vertex_Positon_Normal_Texcoord);
	//	subMeshDesc.indexDataSize = mesh.indices.size() * sizeof(unsigned int);
	//	meshBlobHolder->m_subMeshDescs.push_back(subMeshDesc);

	//	unsigned int length = mesh.vertices.size() * sizeof(Vertex_Positon_Normal_Texcoord) + mesh.indices.size() * sizeof(unsigned int);

	//	Blob* blob = new Blob(length);
	//	memcpy_s(blob->getData(), blob->getLength(), meshes.data(), blob->getLength());
	//	meshBlobHolder->loadSucceeded__(blob);
	//	SAFE_DELETE_SET_NULL(blob);



	//	meshes.clear();
	//	meshes.resize(1);
	//	meshes[0].vertices.resize(1);
	//	meshes[0].indices.resize(3);

	//	memcpy_s(meshes[0].vertices.data(), meshBlobHolder->getSubMeshDescs()[0].vertexDataSize, (char*)meshBlobHolder->getBlob() + meshBlobHolder->getSubMeshDescs()[0].vertexDataOffset, meshBlobHolder->getSubMeshDescs()[0].vertexDataSize);
	//	memcpy_s(meshes[0].indices.data(), meshBlobHolder->getSubMeshDescs()[0].indexDataSize, (char*)meshBlobHolder->getBlob() + meshBlobHolder->getSubMeshDescs()[0].indexDataOffset, meshBlobHolder->getSubMeshDescs()[0].indexDataSize);

	//	m_mtx.unlock();
	//}
}