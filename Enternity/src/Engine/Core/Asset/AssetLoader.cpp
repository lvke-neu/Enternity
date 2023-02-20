#include "AssetLoader.h"
#include "Asset.h"
#include "Core/Log/Log.h"
#include "Core/ThreadPool/ThreadPool.h"
#include "Core/Memory/Blob.h"
#include "Core/Memory/stb_image.h"
#include <fstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Enternity
{
	void AssetLoader::loadAsset(Asset& asset)
	{
		if (asset.m_assetType == AssetType::Shader)
		{
			if (asset.m_assetLoadType == AssetLoadType::Sync)
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
		else if(asset.m_assetType == AssetType::Texture)
		{
				if (asset.m_assetLoadType == AssetLoadType::Sync)
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
			if (asset.m_assetLoadType == AssetLoadType::Sync)
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


	void AssetLoader::loadShaderImpl(Asset& asset)
	{
		std::ifstream ifs(asset.getAssetID(), std::ios::in | std::ios::binary);
		if (!ifs.is_open())
		{
			asset.m_assetLoadState = AssetLoadState::Failure;
			LOG_ERROR("Assets load failed:{0}", asset.getAssetID());
			return;
		}

		asset.reset();

		std::filebuf* pFilebuf = ifs.rdbuf();
		size_t size = pFilebuf->pubseekoff(0, ifs.end, ifs.in);
		pFilebuf->pubseekpos(0, ifs.in);

		asset.m_blob = new Blob(size);
		pFilebuf->sgetn((char*)asset.m_blob->getData(), asset.m_blob->getLength());

		ifs.close();

		asset.m_assetLoadState = AssetLoadState::Success;
	}

	void AssetLoader::loadTextureImpl(Asset& asset)
	{
		unsigned char* tmpTexture;
		int width;
		int height;
		int channels;

		stbi_set_flip_vertically_on_load(1);
		tmpTexture = stbi_load(asset.getAssetID().c_str(), &width, &height, &channels, 0);
		if (!tmpTexture)
		{
			asset.m_assetLoadState = AssetLoadState::Failure;
			LOG_ERROR("Assets load failed:{0}", asset.getAssetID());
			return;
		}

		asset.reset();

		asset.m_blob = new Blob(width * height * channels);
		memcpy_s(asset.m_blob->getData(), asset.m_blob->getLength(), tmpTexture, asset.m_blob->getLength());
		asset.m_blob->m_width = width;
		asset.m_blob->m_height = height;
		asset.m_blob->m_channels = channels;

		stbi_image_free(tmpTexture);

		asset.m_assetLoadState = AssetLoadState::Success;
	}

	void AssetLoader::loadMeshImpl(Asset& asset)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(asset.getAssetID(), aiProcess_Triangulate | aiProcess_FlipUVs
			| aiProcess_GenNormals | aiProcess_GenBoundingBoxes | aiProcess_GenUVCoords | aiProcess_JoinIdenticalVertices);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG_ERROR("ERROR::ASSIMP::{0}", importer.GetErrorString());
			asset.m_assetLoadState = AssetLoadState::Failure;
			return;
		}

		asset.reset();

		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* assimpMesh = scene->mMeshes[i];
			Mesh mesh;
			for (unsigned int j = 0; j < assimpMesh->mNumVertices; j++)
			{
				VertexPosNorTex vertex;
				vertex.position.x = assimpMesh->mVertices[j].x;
				vertex.position.y = assimpMesh->mVertices[j].y;
				vertex.position.z = assimpMesh->mVertices[j].z;

				mesh.vertices.push_back(vertex);
				//TODO: normal and texcoord
			}

			for (unsigned int j = 0; j < assimpMesh->mNumFaces; j++)
			{
				for (unsigned int k = 0; k < assimpMesh->mFaces[i].mNumIndices; k++)
				{
					mesh.indices.push_back(assimpMesh->mFaces[j].mIndices[k]);
				}
			}

			asset.m_meshs.push_back(mesh);
		}

		asset.m_assetLoadState = AssetLoadState::Success;
	}
}