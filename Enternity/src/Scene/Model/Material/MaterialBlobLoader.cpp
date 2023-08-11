#include "MaterialBlobLoader.h"
#include "MaterialBlobHolder.h"
#include "Engine/Engine.h"
#include "Engine/BlobLoaderManager.h"
#include "Engine/BlobLoader.h"
#include "Engine/Log.h"
#include "Graphics/RHI/Texture/TextureBlobHolder.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/gtc/quaternion.hpp>

namespace Enternity
{
	MaterialBlobLoader::MaterialBlobLoader() : BlobLoader("material://")
	{

	}

	BlobHolder* MaterialBlobLoader::createBlobHolder(const char* path)
	{
		return new MaterialBlobHolder(this, path);
	}

	void MaterialBlobLoader::doLoad(BlobHolder* blobHolder)
	{
		MaterialBlobHolder* materialBlobHolder = dynamic_cast<MaterialBlobHolder*>(blobHolder);
		if (!materialBlobHolder || materialBlobHolder->getLoadingState() != BlobHolder::loading_state_pending)
			return;

		m_mtx.lock();

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(materialBlobHolder->getPath(), aiProcess_Triangulate | aiProcess_FlipUVs
			| aiProcess_GenNormals | aiProcess_GenUVCoords | aiProcess_JoinIdenticalVertices);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			materialBlobHolder->loadFailed__();
			LOG_ERROR("ERROR::ASSIMP::{0}", importer.GetErrorString());
			m_mtx.unlock();
			return;
		}

		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];

			//material
			MaterialProperty materialProperty;
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			aiString str;
			aiColor4D color;
			std::string tmpPath;

			BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader("texture://");

			material->Get(AI_MATKEY_COLOR_AMBIENT, color);
			material->GetTexture(aiTextureType_AMBIENT, 0, &str);
			tmpPath = materialBlobHolder->getPath();
			tmpPath = "texture://TEXTURE_2D?" + tmpPath.substr(0, tmpPath.rfind("/") + 1) + str.C_Str();
			materialProperty.m_ambientColor = glm::vec4(color.r, color.g, color.b, color.a);
			materialProperty.m_ambientTextureBlobHolder = (Texture2DBlobHolder*)blobLoader->createBlobHolder(tmpPath.c_str());
			materialProperty.m_ambientTextureBlobHolder->load(0);

			material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
			material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
			tmpPath = materialBlobHolder->getPath();
			tmpPath = "texture://TEXTURE_2D?" + tmpPath.substr(0, tmpPath.rfind("/") + 1) + str.C_Str();
			materialProperty.m_diffuseColor = glm::vec4(color.r, color.g, color.b, color.a);
			materialProperty.m_diffuseTextureBlobHolder = (Texture2DBlobHolder*)blobLoader->createBlobHolder(tmpPath.c_str());
			materialProperty.m_diffuseTextureBlobHolder->load(0);


			material->Get(AI_MATKEY_COLOR_SPECULAR, color);
			material->GetTexture(aiTextureType_SPECULAR, 0, &str);
			tmpPath = materialBlobHolder->getPath();
			tmpPath = "texture://TEXTURE_2D?" + tmpPath.substr(0, tmpPath.rfind("/") + 1) + str.C_Str();
			materialProperty.m_specularColor = glm::vec4(color.r, color.g, color.b, color.a);
			materialProperty.m_specularTextureBlobHolder = (Texture2DBlobHolder*)blobLoader->createBlobHolder(tmpPath.c_str());
			materialProperty.m_specularTextureBlobHolder->load(0);

			materialBlobHolder->m_materialProperties.push_back(materialProperty);
		}

		materialBlobHolder->loadSucceeded__(nullptr);

		m_mtx.unlock();
	}
}