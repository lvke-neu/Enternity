#include "ModelBlobLoader.h"
#include "Engine/Engine.h"
#include "Engine/Blob.h"
#include "Engine/Log.h"
#include "Engine/BlobLoaderManager.h"
#include "ModelBlobHolder.h"
#include "Animation.h"
#include "Graphics/RHI/Mesh/MeshBlobHolder.h"
#include "Graphics/RHI/Texture/TextureBlobHolder.h"
#include "Common/Macro.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include<glm/gtc/quaternion.hpp>


namespace Enternity
{
	static std::map<std::string, BoneInfo> s_boneInfoMap;
	static int s_boneCounter;

	static glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4& from)
	{
		glm::mat4 to;
		//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
		to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
		to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
		to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
		to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
		return to;
	}

	static glm::vec3 GetGLMVec(const aiVector3D& vec)
	{
		return glm::vec3(vec.x, vec.y, vec.z);
	}

	static glm::quat GetGLMQuat(const aiQuaternion& pOrientation)
	{
		return glm::quat(pOrientation.w, pOrientation.x, pOrientation.y, pOrientation.z);
	}

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

		s_boneInfoMap.clear();
		s_boneCounter = 0;

		processNode(modelBlobHolder, scene->mRootNode, scene);

		for (int i = 0; i < scene->mNumAnimations; i++)
		{
			modelBlobHolder->m_animations.push_back(new Animation(scene, i, s_boneInfoMap, s_boneCounter));
		}

		modelBlobHolder->loadSucceeded__(nullptr);

		m_mtx.unlock();
	}

	void ModelBlobLoader::processNode(BlobHolder* blobHolder, aiNode* node, const aiScene* scene)
	{
		ModelBlobHolder* modelBlobHolder = dynamic_cast<ModelBlobHolder*>(blobHolder);

		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{	
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			modelBlobHolder->m_meshBlobHolders.push_back(processMesh(modelBlobHolder, mesh, scene));
			modelBlobHolder->m_texture2DBlobHolders.push_back(processMaterial(modelBlobHolder->m_path, material));
		}
	
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(modelBlobHolder, node->mChildren[i], scene);
		}
	}

	MeshBlobHolder* ModelBlobLoader::processMesh(BlobHolder* blobHolder, aiMesh* mesh, const aiScene* scene)
	{
		ModelBlobHolder* modelBlobHolder = dynamic_cast<ModelBlobHolder*>(blobHolder);

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
			//vertex.m_boneIDs[0] = -1;
			//vertex.m_boneIDs[1] = -1;
			//vertex.m_boneIDs[2] = -1;
			//vertex.m_boneIDs[3] = -1;
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

		//process bone
		for (unsigned int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
		{
			int boneID = -1;
			std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
			if (s_boneInfoMap.find(boneName) == s_boneInfoMap.end())
			{
				BoneInfo newBoneInfo;
				newBoneInfo.id = s_boneCounter;
				newBoneInfo.offset = ConvertMatrixToGLMFormat(mesh->mBones[boneIndex]->mOffsetMatrix);
				s_boneInfoMap[boneName] = newBoneInfo;
				boneID = s_boneCounter;
				s_boneCounter++;
			}
			else
			{
				boneID = s_boneInfoMap[boneName].id;
			}
			assert(boneID != -1);
			auto weights = mesh->mBones[boneIndex]->mWeights;
			int numWeights = mesh->mBones[boneIndex]->mNumWeights;

			for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
			{
				int vertexId = weights[weightIndex].mVertexId;
				float weight = weights[weightIndex].mWeight;

				for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
				{

					if (meshData.vertices[vertexId].m_boneIDs[i] < 0)
					{
						meshData.vertices[vertexId].m_weights[i] = weight;
						meshData.vertices[vertexId].m_boneIDs[i] = boneID;
						break;
					}
				}
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

		return meshBlobHolder;
	}

	Texture2DBlobHolder* ModelBlobLoader::processMaterial(const std::string& path, aiMaterial* material)
	{
		aiString str;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &str);

		std::string tmpPath = "texture://TEXTURE_2D?" + path.substr(0, path.rfind("/") + 1) + str.C_Str();

		aiColor4D color;

		material->Get(AI_MATKEY_COLOR_DIFFUSE, color);

		BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(tmpPath.c_str());
		if (blobLoader)
		{
			BlobHolder* blobHolder = blobLoader->createBlobHolder(tmpPath.c_str());
			if (blobHolder)
			{
				blobHolder->load(0);
			}
			return dynamic_cast<Texture2DBlobHolder*>(blobHolder);
		}

		return nullptr;
	}
}