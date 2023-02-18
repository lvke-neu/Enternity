#include "AssetLoader.h"
#include "Asset.h"
#include "Core/Basic/Macro.h"
#include "Core/Log/Log.h"
#include "Core/ThreadPool/ThreadPool.h"
#include "Core/Memory/Blob.h"
#include "Core/Memory/stb_image.h"
#include "Function/Scene/ECS/Component/MeshRenderComponents.hpp"
#include <fstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Enternity
{
	void AssetLoader::loadAsset(Asset* asset)
	{
		if (asset->m_assetType == AssetType::Shader)
		{
			if (asset->m_assetLoadType == AssetLoadType::Sync)
			{
				loadShaderImpl(asset);
			}
			else
			{
				ThreadPool::GetInstance().commitTask(
					[&]()
					{
						loadShaderImpl(asset);
					});
			}
		}
		else if(asset->m_assetType == AssetType::Texture)
		{
				if (asset->m_assetLoadType == AssetLoadType::Sync)
				{
					loadTextureImpl(asset);
				}
				else
				{
					ThreadPool::GetInstance().commitTask(
						[&]()
						{
							loadTextureImpl(asset);
						});
				}
		}
		else
		{	
			if (asset->m_assetLoadType == AssetLoadType::Sync)
			{
				loadMeshImpl(asset);
			}
			else
			{
				ThreadPool::GetInstance().commitTask(
					[&]()
					{
						loadMeshImpl(asset);
					});
			}
		}
	}

	void AssetLoader::loadShaderImpl(Asset* asset)
	{
		ENTERNITY_ASSERT(asset != nullptr);

		std::ifstream ifs(asset->getAssetID(), std::ios::in | std::ios::binary);
		if (!ifs.is_open())
		{
			asset->m_assetLoadState = AssetLoadState::failure;
			LOG_ERROR("Assets load failed:{0}", asset->getAssetID());
			return;
		}

		std::filebuf* pFilebuf = ifs.rdbuf();
		size_t size = pFilebuf->pubseekoff(0, ifs.end, ifs.in);
		pFilebuf->pubseekpos(0, ifs.in);

		asset->m_blob[0] = new Blob(size);
		pFilebuf->sgetn((char*)asset->m_blob[0]->getData(), asset->m_blob[0]->getLength());

		ifs.close();

		asset->m_assetLoadState = AssetLoadState::success;
	}

	void AssetLoader::loadTextureImpl(Asset* asset)
	{
		ENTERNITY_ASSERT(asset != nullptr);

		unsigned char* tmpTexture;
		int width;
		int height;
		int channels;

		stbi_set_flip_vertically_on_load(1);
		tmpTexture = stbi_load(asset->getAssetID().c_str(), &width, &height, &channels, 0);
		if (!tmpTexture)
		{
			asset->m_assetLoadState = AssetLoadState::failure;
			LOG_ERROR("Assets load failed:{0}", asset->getAssetID());
			return;
		}

		asset->m_blob[0] = new Blob(width * height * channels);
		memcpy_s(asset->m_blob[0]->getData(), asset->m_blob[0]->getLength(), tmpTexture, asset->m_blob[0]->getLength());
		asset->m_blob[0]->m_width = width;
		asset->m_blob[0]->m_height = height;
		asset->m_blob[0]->m_channels = channels;

		stbi_image_free(tmpTexture);

		asset->m_assetLoadState = AssetLoadState::success;
	}

	void AssetLoader::loadMeshImpl(Asset* asset)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(asset->getAssetID(), aiProcess_Triangulate | aiProcess_FlipUVs
			| aiProcess_GenNormals | aiProcess_GenBoundingBoxes | aiProcess_GenUVCoords | aiProcess_JoinIdenticalVertices);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG_ERROR("ERROR::ASSIMP::{0}", importer.GetErrorString());
			asset->m_assetLoadState = AssetLoadState::failure;
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

		asset->m_blob[0] = new Blob(vertices.size() * sizeof(MeshComponent::VertexPosNorTex));
		asset->m_blob[0]->copyDataFrom(vertices.data());

		asset->m_blob[1] = new Blob(indices.size() * sizeof(unsigned int));
		asset->m_blob[1]->copyDataFrom(indices.data());

		asset->m_assetLoadState = AssetLoadState::success;
	}
}