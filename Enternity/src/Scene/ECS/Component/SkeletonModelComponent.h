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

	Assimp::Importer* importer;
	std::string m_ModelFilePath{ "" };
	long long StartTimeMillis = 0;
	const aiScene* m_scene{ nullptr };
	glm::mat4 m_GlobalInverseTransform;
	

	void Load()
	{
		m_Material.m_ShaderFilePath = "assets/shaders/SkeletonModel.glsl";

		UnLoad();

		importer = new Assimp::Importer;
		const aiScene* scene = importer->ReadFile(m_ModelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs
			| aiProcess_GenNormals | aiProcess_GenBoundingBoxes | aiProcess_GenUVCoords);

		m_scene = scene;
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG_ERROR("ERROR::ASSIMP::" + importer->GetErrorString());
			return;
		}

		m_GlobalInverseTransform = AssimpMat4ToGlmMat4(m_scene->mRootNode->mTransformation);
		m_GlobalInverseTransform = glm::inverse(m_GlobalInverseTransform);

		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			ProcessSingleMesh(scene->mMeshes[i], scene, i);
		}


		//ReadNodeHierarchy(scene->mRootNode, glm::mat4(1.0f));

		for (int i = 0; i < m_vertices.size(); i++)
		{
			SkeletonMeshComponent meshc;
			meshc.Load(m_vertices[i].data(), m_vertices[i].size(), m_indices[i].data(), m_indices[i].size());
			m_Mesh.push_back(meshc);
		}

		m_Material.Load();

		StartTimeMillis = GetCurrentTimeMillis();
	}


	void UnLoad()
	{
		for (int i = 0; i < m_Mesh.size(); i++)
			m_Mesh[i].UnLoad();

		m_Material.UnLoad();

		m_vertices.clear();
		m_indices.clear();
		m_BoneNameToIndexMap.clear();
		m_BoneInfo.clear();
		SAFE_DELETE_SET_NULL(importer);
	}

	void CalcuFinalTransform()
	{
		ReadNodeHierarchy(m_scene->mRootNode, glm::mat4(1.0f));
	}

	void CalcuFinalTransform(float TimeInSeconds)
	{
		float TicksPerSecond = (float)(m_scene->mAnimations[0]->mTicksPerSecond != 0 ? m_scene->mAnimations[0]->mTicksPerSecond : 25.0f);
		float TimeInTicks = TimeInSeconds * TicksPerSecond;
		float AnimationTimeTicks = fmod(TimeInTicks, (float)m_scene->mAnimations[0]->mDuration);
		ReadNodeHierarchy(AnimationTimeTicks, m_scene->mRootNode, glm::mat4(1.0f));
	}

	long long GetCurrentTimeMillis()
	{
#ifdef _WIN32
		return GetTickCount();
#else
		timeval t;
		gettimeofday(&t, NULL);

		long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
		return ret;
#endif
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


	const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string& NodeName)
	{
		for (unsigned int i = 0; i < pAnimation->mNumChannels; i++) {
			const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

			if (std::string(pNodeAnim->mNodeName.data) == NodeName) {
				return pNodeAnim;
			}
		}

		return NULL;
	}

	unsigned int FindScaling(float AnimationTimeTicks, const aiNodeAnim* pNodeAnim)
	{
		assert(pNodeAnim->mNumScalingKeys > 0);

		for (unsigned int i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
			float t = (float)pNodeAnim->mScalingKeys[i + 1].mTime;
			if (AnimationTimeTicks < t) {
				return i;
			}
		}

		return 0;
	}

	unsigned int FindRotation(float AnimationTimeTicks, const aiNodeAnim* pNodeAnim)
	{
		assert(pNodeAnim->mNumRotationKeys > 0);

		for (unsigned i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
			float t = (float)pNodeAnim->mRotationKeys[i + 1].mTime;
			if (AnimationTimeTicks < t) {
				return i;
			}
		}

		return 0;
	}

	unsigned int FindPosition(float AnimationTimeTicks, const aiNodeAnim* pNodeAnim)
	{
		for (unsigned int i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
			float t = (float)pNodeAnim->mPositionKeys[i + 1].mTime;
			if (AnimationTimeTicks < t) {
				return i;
			}
		}

		return 0;
	}


	void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTimeTicks, const aiNodeAnim* pNodeAnim)
	{
		// we need at least two values to interpolate...
		if (pNodeAnim->mNumScalingKeys == 1) {
			Out = pNodeAnim->mScalingKeys[0].mValue;
			return;
		}

		unsigned int ScalingIndex = FindScaling(AnimationTimeTicks, pNodeAnim);
		unsigned int NextScalingIndex = ScalingIndex + 1;
		assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
		float t1 = (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime;
		float t2 = (float)pNodeAnim->mScalingKeys[NextScalingIndex].mTime;
		float DeltaTime = t2 - t1;
		float Factor = (AnimationTimeTicks - (float)t1) / DeltaTime;
		assert(Factor >= 0.0f && Factor <= 1.0f);
		const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
		const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
		aiVector3D Delta = End - Start;
		Out = Start + Factor * Delta;
	}

	void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTimeTicks, const aiNodeAnim* pNodeAnim)
	{
		// we need at least two values to interpolate...
		if (pNodeAnim->mNumRotationKeys == 1) {
			Out = pNodeAnim->mRotationKeys[0].mValue;
			return;
		}

		unsigned int RotationIndex = FindRotation(AnimationTimeTicks, pNodeAnim);
		unsigned NextRotationIndex = RotationIndex + 1;
		assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
		float t1 = (float)pNodeAnim->mRotationKeys[RotationIndex].mTime;
		float t2 = (float)pNodeAnim->mRotationKeys[NextRotationIndex].mTime;
		float DeltaTime = t2 - t1;
		float Factor = (AnimationTimeTicks - t1) / DeltaTime;
		assert(Factor >= 0.0f && Factor <= 1.0f);
		const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
		const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
		aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
		Out.Normalize();
	}


	void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTimeTicks, const aiNodeAnim* pNodeAnim)
	{
		// we need at least two values to interpolate...
		if (pNodeAnim->mNumPositionKeys == 1) {
			Out = pNodeAnim->mPositionKeys[0].mValue;
			return;
		}

		unsigned int PositionIndex = FindPosition(AnimationTimeTicks, pNodeAnim);
		unsigned int NextPositionIndex = PositionIndex + 1;
		assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
		float t1 = (float)pNodeAnim->mPositionKeys[PositionIndex].mTime;
		float t2 = (float)pNodeAnim->mPositionKeys[NextPositionIndex].mTime;
		float DeltaTime = t2 - t1;
		float Factor = (AnimationTimeTicks - t1) / DeltaTime;
		assert(Factor >= 0.0f && Factor <= 1.0f);
		const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
		const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
		aiVector3D Delta = End - Start;
		Out = Start + Factor * Delta;
	}

	void ReadNodeHierarchy(float TimeInSeconds, const aiNode* pNode, const glm::mat4& ParentTransform)
	{
		std::string NodeName(pNode->mName.data);

		const aiAnimation* pAnimation = m_scene->mAnimations[0];

		glm::mat4 NodeTransformation(AssimpMat4ToGlmMat4(pNode->mTransformation));

		const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);

		if (pNodeAnim) {
			// Interpolate scaling and generate scaling transformation matrix
			aiVector3D Scaling;
			CalcInterpolatedScaling(Scaling, TimeInSeconds, pNodeAnim);
			glm::mat4 ScalingM = 
			{ Scaling.x, 0.0f,   0.0f,   0.0f,
			  0.0f,   Scaling.y, 0.0f, 0.0f,
			  0.0f,   0.0f, Scaling.z, 0.0f,
			  0.0f,   0.0f, 0.0f, 1.0f
			}; 

			// Interpolate rotation and generate rotation transformation matrix
			aiQuaternion RotationQ;
			CalcInterpolatedRotation(RotationQ, TimeInSeconds, pNodeAnim);
			aiMatrix3x3 mat3x3 = RotationQ.GetMatrix();
			aiMatrix4x4 mat4x4 = {
				mat3x3.a1, mat3x3.a2, mat3x3.a3,	0.0f,
				mat3x3.b1, mat3x3.b2, mat3x3.b3,	0.0f,
				mat3x3.c1, mat3x3.c2, mat3x3.c3,	0.0f,
				0.0f,		0.0f,		0.0f,		1.0f
			};
			glm::mat4 RotationM = AssimpMat4ToGlmMat4(mat4x4);

			// Interpolate translation and generate translation transformation matrix
			aiVector3D Translation;
			CalcInterpolatedPosition(Translation, TimeInSeconds, pNodeAnim);
			glm::mat4 TranslationM;
			TranslationM = 
			{
				1.0f,  0.0f, 0.0f,  Translation.x,
				0.0f,  1.0f, 0.0f,  Translation.y,
				0.0f,  0.0f, 1.0f,  Translation.z,
				0.0f,  0.0f, 0.0f,  1.0f
			}; 
			
	
			// Combine the above transformations
			//NodeTransformation = TranslationM * RotationM * ScalingM;
			NodeTransformation =  ScalingM * RotationM * TranslationM;
		}

		//notice glm matrix multiplication : need Swap two matrix's positions  !!!!!!!
		glm::mat4 GlobalTransformation = NodeTransformation * ParentTransform;

		if (m_BoneNameToIndexMap.find(NodeName) != m_BoneNameToIndexMap.end()) {
			unsigned int BoneIndex = m_BoneNameToIndexMap[NodeName];

			//notice glm matrix multiplication : need Swap two matrix's positions !!!!!!!!!!
			m_BoneInfo[BoneIndex].FinalTransformation = m_BoneInfo[BoneIndex].OffsetMatrix * GlobalTransformation * m_GlobalInverseTransform;
		}

		for (unsigned i = 0; i < pNode->mNumChildren; i++) {
			ReadNodeHierarchy(TimeInSeconds, pNode->mChildren[i], GlobalTransformation);
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

