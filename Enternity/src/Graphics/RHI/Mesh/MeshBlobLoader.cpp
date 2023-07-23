#include "MeshBlobLoader.h"
#include "MeshBlobHolder.h"
#include "Engine/Log.h"
#include "Engine/Blob.h"
#include "Common/Macro.h"

namespace Enternity
{
	MeshBlobLoader::MeshBlobLoader() : BlobLoader("mesh://")
	{

	}

	BlobHolder* MeshBlobLoader::createBlobHolder(const char* path)
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

		m_mtx.lock();

		if (strcmp(meshBlobHolder->getPath(), "primitive=cube")  == 0)
		{
			loadCube(meshBlobHolder);
		}
		else if (strcmp(meshBlobHolder->getPath(), "primitive=plane") == 0)
		{
			loadPlane(meshBlobHolder);
		}
		else
		{
			LOG_ERROR("Mesh load failed:{0}, Not support type", meshBlobHolder->getPath());
			meshBlobHolder->loadFailed__();
		}

		m_mtx.unlock();
	}

	void MeshBlobLoader::loadCube(MeshBlobHolder* meshBlobHolder)
	{
		std::vector<Vertex_Positon_Normal_Texcoord> vertices;
		vertices.resize(24);

		vertices[0].position = glm::vec3(1, -1, 1);
		vertices[1].position = glm::vec3(1, 1, 1);
		vertices[2].position = glm::vec3(1, 1, -1);
		vertices[3].position = glm::vec3(1, -1, -1);

		vertices[4].position = glm::vec3(-1, -1, -1);
		vertices[5].position = glm::vec3(-1, 1, -1);
		vertices[6].position = glm::vec3(-1, 1, 1);
		vertices[7].position = glm::vec3(-1, -1, 1);

		vertices[8].position = glm::vec3(-1, 1, 1);
		vertices[9].position = glm::vec3(-1, 1, -1);
		vertices[10].position = glm::vec3(1, 1, -1);
		vertices[11].position = glm::vec3(1, 1, 1);

		vertices[12].position = glm::vec3(1, -1, 1);
		vertices[13].position = glm::vec3(1, -1, -1);
		vertices[14].position = glm::vec3(-1, -1, -1);
		vertices[15].position = glm::vec3(-1, -1, 1);

		vertices[16].position = glm::vec3(1, -1, -1);
		vertices[17].position = glm::vec3(1, 1, -1);
		vertices[18].position = glm::vec3(-1, 1, -1);
		vertices[19].position = glm::vec3(-1, -1, -1);

		vertices[20].position = glm::vec3(-1, -1, 1);
		vertices[21].position = glm::vec3(-1, 1, 1);
		vertices[22].position = glm::vec3(1, 1, 1);
		vertices[23].position = glm::vec3(1, -1, 1);

		for (UINT i = 0; i < 4; ++i)
		{
			vertices[i].normal = glm::vec3(1.0f, 0.0f, 0.0f);

			vertices[i + 4].normal = glm::vec3(-1.0f, 0.0f, 0.0f);

			vertices[i + 8].normal = glm::vec3(0.0f, 1.0f, 0.0f);

			vertices[i + 12].normal = glm::vec3(0.0f, -1.0f, 0.0f);

			vertices[i + 16].normal = glm::vec3(0.0f, 0.0f, -1.0f);

			vertices[i + 20].normal = glm::vec3(0.0f, 0.0f, 1.0f);
		}

		for (UINT i = 0; i < 6; ++i)
		{
			vertices[i * 4].texcoord = glm::vec2(0.0f, 0.0f);
			vertices[i * 4 + 1].texcoord = glm::vec2(0.0f, 1.0f);
			vertices[i * 4 + 2].texcoord = glm::vec2(1.0f, 1.0f);
			vertices[i * 4 + 3].texcoord = glm::vec2(1.0f, 0.0f);
		}

		std::vector<unsigned int> indices = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4,
			8, 9, 10, 10, 11, 8,
			12, 13, 14, 14, 15, 12,
			16, 17, 18, 18, 19, 16,
			20, 21, 22, 22, 23, 20
		};

		meshBlobHolder->m_meshDesc.vertexDataOffset = 0;
		meshBlobHolder->m_meshDesc.vertexDataSize = (unsigned int)vertices.size() * sizeof(Vertex_Positon_Normal_Texcoord);
		meshBlobHolder->m_meshDesc.indexDataOffset = meshBlobHolder->m_meshDesc.vertexDataSize;
		meshBlobHolder->m_meshDesc.indexDataSize = (unsigned int)indices.size() * sizeof(unsigned int);
		meshBlobHolder->m_layout = Vertex_Positon_Normal_Texcoord::s_layout;

		Blob* blob = new Blob(meshBlobHolder->m_meshDesc.vertexDataSize + meshBlobHolder->m_meshDesc.indexDataSize);
		memcpy_s((char*)blob->getData() + meshBlobHolder->m_meshDesc.vertexDataOffset,
			meshBlobHolder->m_meshDesc.vertexDataSize,
			vertices.data(),
			meshBlobHolder->m_meshDesc.vertexDataSize);
		memcpy_s((char*)blob->getData() + meshBlobHolder->m_meshDesc.indexDataOffset,
			meshBlobHolder->m_meshDesc.indexDataSize,
			indices.data(),
			meshBlobHolder->m_meshDesc.indexDataSize);
		meshBlobHolder->loadSucceeded__(blob);

		SAFE_DELETE_SET_NULL(blob);
	}

	void MeshBlobLoader::loadPlane(MeshBlobHolder* meshBlobHolder)
	{
		std::vector<Vertex_Positon_Normal_Texcoord> vertices;

		vertices.resize(4);
		vertices[0].position = glm::vec3(-1, 1, 0);
		vertices[1].position = glm::vec3(1, 1, 0);
		vertices[2].position = glm::vec3(1, -1, 0);
		vertices[3].position = glm::vec3(-1, -1, 0);

		vertices[0].normal = glm::vec3(0, 0, 1);
		vertices[1].normal = glm::vec3(0, 0, 1);
		vertices[2].normal = glm::vec3(0, 0, 1);
		vertices[3].normal = glm::vec3(0, 0, 1);

		vertices[0].texcoord = glm::vec2(0, 1);
		vertices[1].texcoord = glm::vec2(1, 1);
		vertices[2].texcoord = glm::vec2(1, 0);
		vertices[3].texcoord = glm::vec2(0, 0);

		std::vector<unsigned int> indices = { 0, 3, 2, 0, 2, 1 };

		meshBlobHolder->m_meshDesc.vertexDataOffset = 0;
		meshBlobHolder->m_meshDesc.vertexDataSize = (unsigned int)vertices.size() * sizeof(Vertex_Positon_Normal_Texcoord);
		meshBlobHolder->m_meshDesc.indexDataOffset = meshBlobHolder->m_meshDesc.vertexDataSize;
		meshBlobHolder->m_meshDesc.indexDataSize = (unsigned int)indices.size() * sizeof(unsigned int);
		meshBlobHolder->m_layout = Vertex_Positon_Normal_Texcoord::s_layout;

		Blob* blob = new Blob(meshBlobHolder->m_meshDesc.vertexDataSize + meshBlobHolder->m_meshDesc.indexDataSize);
		memcpy_s((char*)blob->getData() + meshBlobHolder->m_meshDesc.vertexDataOffset,
			meshBlobHolder->m_meshDesc.vertexDataSize,
			vertices.data(),
			meshBlobHolder->m_meshDesc.vertexDataSize);
		memcpy_s((char*)blob->getData() + meshBlobHolder->m_meshDesc.indexDataOffset,
			meshBlobHolder->m_meshDesc.indexDataSize,
			indices.data(),
			meshBlobHolder->m_meshDesc.indexDataSize);
		meshBlobHolder->loadSucceeded__(blob);

		SAFE_DELETE_SET_NULL(blob);
	}
}