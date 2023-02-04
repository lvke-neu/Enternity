#include "Component.h"

BEGIN_ENTERNITY
//skeleton
struct SkeletonMeshComponent
{
	struct VertexPosTex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoord;
		glm::ivec4 boneIds{ 0 };
		glm::vec4 weights{ 0 };
	};

	VertexArray* m_VertexArray{ nullptr };
	VertexBuffer* m_Vertexbuffer{ nullptr };
	IndexBuffer* m_Indexbuffer{ nullptr };

	std::string m_MeshFilePath{ "" };

	SkeletonMeshComponent() = default;
	SkeletonMeshComponent(const SkeletonMeshComponent&) = default;

	//load mesh by m_MeshFilePath
	void Load()
	{
		auto pos = m_MeshFilePath.find(".");
		if (pos == std::string::npos)
			return;
		std::string suffix = m_MeshFilePath.substr(pos, m_MeshFilePath.size() - 1);
		if (suffix != ".mesh")
			return;

		Enternity::Blob blob2(DEFAULT_BLOB_LENGTH);
		if (!Enternity::FileOperation::ReadFile(blob2, m_MeshFilePath))
			return;

		UnLoad();
		unsigned int vertexcount2;
		unsigned int indexcount2;
		memcpy_s(&vertexcount2, sizeof(unsigned int), blob2.GetData(), sizeof(unsigned int));
		memcpy_s(&indexcount2, sizeof(unsigned int), (char*)blob2.GetData() + sizeof(unsigned int), sizeof(unsigned int));

		VertexPosTex* vpt = new VertexPosTex[vertexcount2];
		unsigned int* indices2 = new unsigned int[indexcount2];
		memcpy_s(vpt, vertexcount2 * sizeof(VertexPosTex), (char*)blob2.GetData() + 2 * sizeof(unsigned int), vertexcount2 * sizeof(VertexPosTex));
		memcpy_s(indices2, indexcount2 * sizeof(unsigned int), (char*)blob2.GetData() + 2 * sizeof(unsigned int) + vertexcount2 * sizeof(VertexPosTex), indexcount2 * sizeof(unsigned int));


		m_Vertexbuffer = new VertexBuffer(vpt, vertexcount2 * sizeof(VertexPosTex));
		m_VertexArray = new VertexArray;
		VertexBufferLayout  vertexBufferLayout;
		vertexBufferLayout.Push({ 0, 3, GL_FLOAT, false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 0 });
		vertexBufferLayout.Push({ 1, 3, GL_FLOAT, false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 3 * sizeof(float) });
		vertexBufferLayout.Push({ 2, 2, GL_FLOAT, false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 6 * sizeof(float) });
		vertexBufferLayout.Push({ 3, 4, GL_INT,   false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 8 * sizeof(float) });
		vertexBufferLayout.Push({ 4, 4, GL_FLOAT, false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 8 * sizeof(float) + 4 * sizeof(unsigned int) });
		m_VertexArray->Add(*m_Vertexbuffer, vertexBufferLayout);
		m_Indexbuffer = new IndexBuffer(indices2, indexcount2);

		delete[] vpt;
		delete[] indices2;
	}

	//load by data
	void Load(const void* vertexData, unsigned int vertexCount, const unsigned int* indexData, unsigned int indexCount)
	{
		m_Vertexbuffer = new VertexBuffer(vertexData, vertexCount * sizeof(VertexPosTex));
		m_VertexArray = new VertexArray;
		VertexBufferLayout  vertexBufferLayout;
		vertexBufferLayout.Push({ 0, 3, GL_FLOAT, false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 0 });
		vertexBufferLayout.Push({ 1, 3, GL_FLOAT, false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 3 * sizeof(float) });
		vertexBufferLayout.Push({ 2, 2, GL_FLOAT, false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 6 * sizeof(float) });
		vertexBufferLayout.Push({ 3, 4, GL_INT,   false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 8 * sizeof(float) });
		vertexBufferLayout.Push({ 4, 4, GL_FLOAT, false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 8 * sizeof(float) + 4 * sizeof(unsigned int) });
		m_VertexArray->Add(*m_Vertexbuffer, vertexBufferLayout);
		m_Indexbuffer = new IndexBuffer(indexData, indexCount);
	}

	void UnLoad()
	{
		SAFE_DELETE_SET_NULL(m_VertexArray);
		SAFE_DELETE_SET_NULL(m_Vertexbuffer);
		SAFE_DELETE_SET_NULL(m_Indexbuffer);
	}
};

struct SkeletonModelComponent
{
	std::vector<SkeletonMeshComponent> m_Mesh;
	MaterialComponent m_Material;
	std::vector<std::vector<SkeletonMeshComponent::VertexPosTex>> m_vertices;
	std::vector<std::vector<unsigned int>> m_indices;

	std::map<std::string, unsigned int> m_BoneNameToIndexMap;


	struct BoneInfo
	{
		glm::mat4 OffsetMatrix;
		glm::mat4 FinalTransformation;

		BoneInfo(const glm::mat4& Offset)
		{
			OffsetMatrix = Offset;
			FinalTransformation = glm::mat4(0);
		}
	};

	std::vector<BoneInfo> m_BoneInfo;


	std::string m_ModelFilePath{ "" };


	void Load()
	{
		m_Material.m_ShaderFilePath = "assets/shaders/SkeletonModel.glsl";

		UnLoad();

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(m_ModelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs
			| aiProcess_GenNormals | aiProcess_GenBoundingBoxes | aiProcess_GenUVCoords);


		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG_ERROR("ERROR::ASSIMP::" + importer.GetErrorString());
			return;
		}

		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			ProcessSingleMesh(scene->mMeshes[i], scene, i);
		}


		ReadNodeHierarchy(scene->mRootNode, glm::mat4(1.0f));

		for (int i = 0; i < m_vertices.size(); i++)
		{
			SkeletonMeshComponent meshc;
			meshc.Load(m_vertices[i].data(), m_vertices[i].size(), m_indices[i].data(), m_indices[i].size());
			m_Mesh.push_back(meshc);
		}

		m_Material.Load();
	}


	void UnLoad()
	{

	}
private:
	glm::mat4 AssimpMat4ToGlmMat4(const aiMatrix4x4& aiMat4)
	{
		return glm::mat4{
			aiMat4.a1, aiMat4.a2, aiMat4.a3, aiMat4.a4,
			aiMat4.b1, aiMat4.b2, aiMat4.b3, aiMat4.b4,
			aiMat4.c1, aiMat4.c2, aiMat4.c3, aiMat4.c4,
			aiMat4.d1, aiMat4.d2, aiMat4.d3, aiMat4.d4,
		};
	}

	void ReadNodeHierarchy(const aiNode* pNode, const glm::mat4& ParentTransform)
	{
		std::string NodeName(pNode->mName.data);

		glm::mat4 NodeTransformation(AssimpMat4ToGlmMat4(pNode->mTransformation));


		//notice glm matrix multiplication : need Swap two matrix's positions  !!!!!!!
		glm::mat4 GlobalTransformation = NodeTransformation * ParentTransform;

		if (m_BoneNameToIndexMap.find(NodeName) != m_BoneNameToIndexMap.end()) {
			unsigned int BoneIndex = m_BoneNameToIndexMap[NodeName];

			//notice glm matrix multiplication : need Swap two matrix's positions !!!!!!!!!!
			m_BoneInfo[BoneIndex].FinalTransformation =  m_BoneInfo[BoneIndex].OffsetMatrix * GlobalTransformation;
		}

		for (unsigned i = 0; i < pNode->mNumChildren; i++) {
			ReadNodeHierarchy(pNode->mChildren[i], GlobalTransformation);
		}
	}


	int GetBoneId(const aiBone* pBone)
	{
		int BoneIndex = 0;
		std::string BoneName(pBone->mName.C_Str());

		if (m_BoneNameToIndexMap.find(BoneName) == m_BoneNameToIndexMap.end()) {
			// Allocate an index for a new bone
			BoneIndex = (int)m_BoneNameToIndexMap.size();
			m_BoneNameToIndexMap[BoneName] = BoneIndex;
		}
		else {
			BoneIndex = m_BoneNameToIndexMap[BoneName];
		}

		return BoneIndex;
	}


	void ProcessSingleMesh(aiMesh* mesh, const aiScene* scene, unsigned int meshIndex)
	{
		//vertex
		std::vector<SkeletonMeshComponent::VertexPosTex> vertedata;
		SkeletonMeshComponent::VertexPosTex tmpVertexPosTex;
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			//position
			tmpVertexPosTex.position.x = mesh->mVertices[i].x;
			tmpVertexPosTex.position.y = mesh->mVertices[i].y;
			tmpVertexPosTex.position.z = mesh->mVertices[i].z;

			//normal
			tmpVertexPosTex.normal.x = mesh->mNormals[i].x;
			tmpVertexPosTex.normal.y = mesh->mNormals[i].y;
			tmpVertexPosTex.normal.z = mesh->mNormals[i].z;

			//texcoord
			if (mesh->HasTextureCoords(0))
			{
				tmpVertexPosTex.texcoord.x = mesh->mTextureCoords[0][i].x;
				tmpVertexPosTex.texcoord.y = -mesh->mTextureCoords[0][i].y + 1;
			}

			vertedata.push_back(tmpVertexPosTex);
		}
		m_vertices.push_back(vertedata);

		//index
		std::vector<unsigned int> indexdata;
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
			{
				indexdata.push_back(mesh->mFaces[i].mIndices[j]);
			}
		}
		m_indices.push_back(indexdata);


		//bone
		for (unsigned int i = 0; i < mesh->mNumBones; i++) {
			int BoneId = GetBoneId(mesh->mBones[i]);

			if (BoneId == m_BoneInfo.size()) {
				BoneInfo bi(AssimpMat4ToGlmMat4(mesh->mBones[i]->mOffsetMatrix));
				m_BoneInfo.push_back(bi);
			}

			for (unsigned j = 0; j < mesh->mBones[i]->mNumWeights; j++) {
				const aiVertexWeight& vw = mesh->mBones[i]->mWeights[j];
				unsigned int GlobalVertexID = m_vertices[meshIndex].size() + mesh->mBones[i]->mWeights[j].mVertexId;

				if (m_vertices[meshIndex][mesh->mBones[i]->mWeights[j].mVertexId].boneIds.x == 0 && m_vertices[meshIndex][mesh->mBones[i]->mWeights[j].mVertexId].weights.x == 0)
				{
					m_vertices[meshIndex][mesh->mBones[i]->mWeights[j].mVertexId].boneIds.x = BoneId;
					m_vertices[meshIndex][mesh->mBones[i]->mWeights[j].mVertexId].weights.x = mesh->mBones[i]->mWeights[j].mWeight;
					continue;
				}
				if (m_vertices[meshIndex][mesh->mBones[i]->mWeights[j].mVertexId].boneIds.y == 0 && m_vertices[meshIndex][mesh->mBones[i]->mWeights[j].mVertexId].weights.y == 0)
				{
					m_vertices[meshIndex][mesh->mBones[i]->mWeights[j].mVertexId].boneIds.y = BoneId;
					m_vertices[meshIndex][mesh->mBones[i]->mWeights[j].mVertexId].weights.y = mesh->mBones[i]->mWeights[j].mWeight;
					continue;
				}
				if (m_vertices[meshIndex][mesh->mBones[i]->mWeights[j].mVertexId].boneIds.z == 0 && m_vertices[meshIndex][mesh->mBones[i]->mWeights[j].mVertexId].weights.z == 0)
				{
					m_vertices[meshIndex][mesh->mBones[i]->mWeights[j].mVertexId].boneIds.z = BoneId;
					m_vertices[meshIndex][mesh->mBones[i]->mWeights[j].mVertexId].weights.z = mesh->mBones[i]->mWeights[j].mWeight;
					continue;
				}
				if (m_vertices[meshIndex][mesh->mBones[i]->mWeights[j].mVertexId].boneIds.w == 0 && m_vertices[meshIndex][mesh->mBones[i]->mWeights[j].mVertexId].weights.w == 0)
				{
					m_vertices[meshIndex][mesh->mBones[i]->mWeights[j].mVertexId].boneIds.w = BoneId;
					m_vertices[meshIndex][mesh->mBones[i]->mWeights[j].mVertexId].weights.w = mesh->mBones[i]->mWeights[j].mWeight;
					continue;
				}
			}
		}
	}

public:
	SkeletonModelComponent() = default;
	SkeletonModelComponent(const SkeletonModelComponent&) = default;
};
END_ENTERNITY

