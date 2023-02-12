#include "BlobLoader.h"
#include "Core/Log/Log.h"
#include "Core/File/Blob.h"
#include "Core/File/stb_image.h"
#include "Core/ThreadPool/ThreadPool.h"
#include "Function/Scene/ECS/Component/MeshRenderComponents.hpp"
#include <fstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Enternity
{
	static int s_desired_channels = 0;

	void BlobLoader::loadGeneral(Blob*& blob, const std::string& filePath, LoadType loadType)
	{
		if (loadType == LoadType::Sync)
			loadGeneralImpl(blob, filePath);
		else if (loadType == LoadType::Asyn)
			ThreadPool::GetInstance().commitTask(
				[&]()
				{
					loadGeneralImpl(blob, filePath);
				});
		else
			blob = nullptr;
	}

	void BlobLoader::loadTexture(Blob*& blob, const std::string& filePath, LoadType loadType, int desired_channels /*= 0*/)
	{
		s_desired_channels = desired_channels;
		if (loadType == LoadType::Sync)
			loadTextureImpl(blob, filePath);
		else if (loadType == LoadType::Asyn)
			ThreadPool::GetInstance().commitTask(
				[&]()
				{
					loadTextureImpl(blob, filePath);
				});
		else
			blob = nullptr;
	}

	void BlobLoader::loadMesh(Blob*& verticesBlob, Blob*& indicesBlob, const std::string& filePath, LoadType loadType)
	{
		if (loadType == LoadType::Sync)
			loadMeshImpl(verticesBlob, indicesBlob, filePath);
		else if (loadType == LoadType::Asyn)
			ThreadPool::GetInstance().commitTask(
				[&]()
				{
					loadMeshImpl(verticesBlob, indicesBlob, filePath);
				});
		else
		{
			verticesBlob = nullptr;
			indicesBlob = nullptr;
		}
	}

	void BlobLoader::loadGeneralImpl(Blob*& blob, const std::string& filePath)
	{
		std::ifstream ifs(filePath, std::ios::in | std::ios::binary);
		ENTERNITY_ASSERT(ifs.is_open());

		std::filebuf* pFilebuf = ifs.rdbuf();
		size_t size = pFilebuf->pubseekoff(0, ifs.end, ifs.in);
		pFilebuf->pubseekpos(0, ifs.in);

		blob = new Blob(size);
		pFilebuf->sgetn((char*)blob->getData(), blob->getLength());

		ifs.close();
	}

	void BlobLoader::loadTextureImpl(Blob*& blob, const std::string& filePath)
	{
		unsigned char* tmpTexture;
		int width;
		int height;
		int channels;

		stbi_set_flip_vertically_on_load(1);
		tmpTexture = stbi_load(filePath.c_str(), &width, &height, &channels, s_desired_channels);

		blob = new Blob(width * height * channels);
		memcpy_s(blob->getData(), blob->getLength(), tmpTexture, blob->getLength());
		blob->m_width = width;
		blob->m_height = height;
		blob->m_channels = channels;

		stbi_image_free(tmpTexture);
	}

	void BlobLoader::loadMeshImpl(Blob*& verticesBlob, Blob*& indicesBlob, const std::string& filePath)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs
			| aiProcess_GenNormals | aiProcess_GenBoundingBoxes | aiProcess_GenUVCoords | aiProcess_JoinIdenticalVertices);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG_ERROR("ERROR::ASSIMP::{0}", importer.GetErrorString());
			verticesBlob = nullptr;
			indicesBlob = nullptr;
			return;
		}

		std::vector<MeshComponent::VertexPosNorTex> vertices;
		std::vector<unsigned int> indices;
		unsigned int indexOffset = 0;
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];
			
			for (unsigned int j = 0; j < mesh->mNumVertices; j++)
			{
				MeshComponent::VertexPosNorTex vertex;
				vertex.position.x = mesh->mVertices[j].x;
				vertex.position.y = mesh->mVertices[j].y;
				vertex.position.z = mesh->mVertices[j].z;

				vertices.push_back(vertex);
				//TODO: normal and texcoord
			}

			for (unsigned int j = 0; j < mesh->mNumFaces; j++)
			{
				for (unsigned int k = 0; k < mesh->mFaces[i].mNumIndices; k++)
				{
					indices.push_back(mesh->mFaces[j].mIndices[k] + indexOffset);
				}
			}

			indexOffset += (unsigned int)vertices.size();
		}

		verticesBlob = new Blob(vertices.size() * sizeof(MeshComponent::VertexPosNorTex));
		verticesBlob->copyDataFrom(vertices.data());

		indicesBlob = new Blob(indices.size() * sizeof(unsigned int));
		indicesBlob->copyDataFrom(indices.data());
	}
}