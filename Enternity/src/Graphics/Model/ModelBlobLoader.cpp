#include "ModelBlobLoader.h"
#include "Engine/Engine.h"
#include "Engine/BlobLoaderManager.h"
#include "Engine/BlobLoader.h"
#include "Engine/Blob.h"
#include "Engine/Log.h"
#include "ModelBlobHolder.h"
#include "Graphics/Material.h"
#include "Graphics/RHI/Mesh/MeshBlobHolder.h"
#include "Graphics/RHI/Texture/TextureBlobHolder.h"
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

		struct MeshData
		{
			std::vector<Vertex_Skeleton> vertices;
			std::vector<unsigned int> indices;
		};
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];


			//mesh
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

			////process bone
			//for (unsigned int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
			//{
			//	int boneID = -1;
			//	std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
			//	if (modelBlobHolder->m_boneInfoMap.find(boneName) == modelBlobHolder->m_boneInfoMap.end())
			//	{
			//		BoneInfo newBoneInfo;
			//		newBoneInfo.id = modelBlobHolder->m_boneCounter;
			//		newBoneInfo.offset = ConvertMatrixToGLMFormat(mesh->mBones[boneIndex]->mOffsetMatrix);
			//		modelBlobHolder->m_boneInfoMap[boneName] = newBoneInfo;
			//		boneID = modelBlobHolder->m_boneCounter;
			//		modelBlobHolder->m_boneCounter++;
			//	}
			//	else
			//	{
			//		boneID = modelBlobHolder->m_boneInfoMap[boneName].id;
			//	}
			//	assert(boneID != -1);
			//	auto weights = mesh->mBones[boneIndex]->mWeights;
			//	int numWeights = mesh->mBones[boneIndex]->mNumWeights;

			//	for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
			//	{
			//		int vertexId = weights[weightIndex].mVertexId;
			//		float weight = weights[weightIndex].mWeight;

			//		for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
			//		{

			//			if (meshData.vertices[vertexId].m_boneIDs[i] < 0)
			//			{
			//				meshData.vertices[vertexId].m_weights[i] = weight;
			//				meshData.vertices[vertexId].m_boneIDs[i] = boneID;
			//				break;
			//			}
			//		}
			//	}
			//}

			meshDesc.indexDataOffset = offset;
			meshDesc.indexDataSize = (unsigned int)meshData.indices.size() * sizeof(unsigned int);
			offset += meshDesc.indexDataSize;

			MeshBlobHolder* meshBlobHolder = new MeshBlobHolder(nullptr, "");
			meshBlobHolder->m_layout = Vertex_Skeleton::s_layout;
			meshBlobHolder->m_meshDesc = meshDesc;
			modelBlobHolder->m_meshNames.push_back(mesh->mName.C_Str());

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

			//material
			Material* material = new Material;
			aiMaterial* aimaterial = scene->mMaterials[mesh->mMaterialIndex];
			aiString str;
			aiColor4D color;
			std::string tmpPath;

			aimaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
			aimaterial->GetTexture(aiTextureType_AMBIENT, 0, &str);
			tmpPath = modelBlobHolder->getPath();
			tmpPath = "texture://TEXTURE_2D?" + tmpPath.substr(0, tmpPath.rfind("/") + 1) + str.C_Str();
			material->set_ambientColor({ color.r, color.g, color.b, color.a });
			material->set_ambientTexturePath(tmpPath);
		
			aimaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
			aimaterial->GetTexture(aiTextureType_DIFFUSE, 0, &str);
			tmpPath = modelBlobHolder->getPath();
			tmpPath = "texture://TEXTURE_2D?" + tmpPath.substr(0, tmpPath.rfind("/") + 1) + str.C_Str();
			material->set_diffuseColor({ color.r, color.g, color.b, color.a });
			material->set_diffuseTexturePath(tmpPath);

			aimaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
			aimaterial->GetTexture(aiTextureType_SPECULAR, 0, &str);
			tmpPath = modelBlobHolder->getPath();
			tmpPath = "texture://TEXTURE_2D?" + tmpPath.substr(0, tmpPath.rfind("/") + 1) + str.C_Str();
			material->set_specularColor({ color.r, color.g, color.b, color.a });
			material->set_specularTexturePath(tmpPath);

			
			material->load();
			modelBlobHolder->m_materials.push_back(material);
		}

		modelBlobHolder->loadSucceeded__(nullptr);

		m_mtx.unlock();
	}
}