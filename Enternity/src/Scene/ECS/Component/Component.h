/***************************************************************************************
Author: lvke
Date:2023/1/10 21:01
Description:
Components
****************************************************************************************/
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Macro/Macro.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/SkyBoxTexture.h"
#include "File/FileOperation.h"
#include <set>
#include <map>

BEGIN_ENTERNITY

struct TagComponent
{
	TagComponent() = default;
	TagComponent(const TagComponent&) = default;
	TagComponent(const std::string& tag)
	{
		m_Tag = tag;
	}
	std::string m_Tag{ "" };
};

//test 
struct MotorComponent
{
	float m_RotationYAnglePerSecond = 45.0f;
	float m_RotationXAnglePerSecond = 45.0f;
	MotorComponent() = default;
	MotorComponent(const MotorComponent&) = default;
	MotorComponent(float angleY, float angleX)
	{
		m_RotationYAnglePerSecond = angleY;
		m_RotationXAnglePerSecond = angleX;
	}
};

struct TransformComponent
{
	glm::vec3 m_Translation{ 0.0f, 0.0f, 0.0f };
	glm::vec3 m_Rotation{ 0.0f, 0.0f, 0.0f };
	glm::vec3 m_Scale{ 1.0f, 1.0f, 1.0f };

	TransformComponent() = default;
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
	{
		m_Translation = translation;
		m_Rotation = rotation;
		m_Scale = scale;
	}

	void Move(float distance, const glm::vec3& direction)
	{
		m_Translation += distance * direction;
	}

	void MoveXAxis(float distance)
	{
		Move(distance,GetRotationMatrix()[0]);
	}

	void MoveZAxis(float distance)
	{
		Move(distance, GetRotationMatrix()[2]);
	}

	void RotateAlongXAxis(float angle)
	{
		m_Rotation.x -= angle;
		if (m_Rotation.x >= 2 * glm::pi<float>())
		{
			m_Rotation.x -= 2 * glm::pi<float>();
		}

		if (m_Rotation.x <= -2 * glm::pi<float>())
		{
			m_Rotation.x = m_Rotation.x + 2 * glm::pi<float>();
		}
	}

	void RotateAlongYAxis(float angle)
	{
		m_Rotation.y -= angle;
		if (m_Rotation.y >= 2 * glm::pi<float>())
		{
			m_Rotation.y -= 2 * glm::pi<float>();
		}

		if (m_Rotation.y <= -2 * glm::pi<float>())
		{
			m_Rotation.y = m_Rotation.y + 2 * glm::pi<float>();
		}
	}

	glm::mat4 GetTranslationMatrix() const
	{
		return glm::translate(glm::mat4(1.0f), m_Translation);
	}

	glm::mat4 GetRotationMatrix() const
	{
		//RollPitchYaw to quaternion, quaternion to rotation matrix
		return glm::mat4_cast(glm::qua<float>(m_Rotation));
	}

	glm::mat4 GetScaleMatrix() const
	{
		return glm::scale(glm::mat4(1.0f), m_Scale);
	}

	glm::mat4 GetWorldMatrix() const
	{
		return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
	}

	glm::mat4 GetInverseWorldMatrix() const
	{
		return glm::inverse(GetWorldMatrix());
	}
};


struct MeshComponent
{
	struct VertexPosTex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoord;
	};

	VertexArray* m_VertexArray{ nullptr };
	VertexBuffer* m_Vertexbuffer{ nullptr };
	IndexBuffer* m_Indexbuffer{ nullptr };

	std::string m_MeshFilePath{ "" };

	MeshComponent() = default;
	MeshComponent(const MeshComponent&) = default;

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
		vertexBufferLayout.Push({ 0, 3, GL_FLOAT, false,  8 * sizeof(float), 0 });
		vertexBufferLayout.Push({ 1, 3, GL_FLOAT, false,  8 * sizeof(float), 3 * sizeof(float) });
		vertexBufferLayout.Push({ 2, 2, GL_FLOAT, false,  8 * sizeof(float), 6 * sizeof(float) });
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
		vertexBufferLayout.Push({ 0, 3, GL_FLOAT, false,  8 * sizeof(float), 0 });
		vertexBufferLayout.Push({ 1, 3, GL_FLOAT, false,  8 * sizeof(float), 3 * sizeof(float) });
		vertexBufferLayout.Push({ 2, 2, GL_FLOAT, false,  8 * sizeof(float), 6 * sizeof(float) });
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


struct MaterialComponent
{
	Shader* m_Shader{ nullptr };
	std::string m_ShaderFilePath{ "assets/shaders/TestECSPhong.glsl" };

	Texture* m_DiffuseTexture{ nullptr };
	std::string m_DiffuseTextureFilePath{ "" };

	Texture* m_SpecularTexture{ nullptr };
	std::string m_SpecularTextureFilePath{ "" };
	
	bool m_UseTexture = false;

	glm::vec4 m_Ambient{ 1.0f };
	glm::vec4 m_Diffuse{ 1.0f };
	glm::vec4 m_Specular{ 1.0f };
	float m_Shininess = 32.0f;

	void Load()
	{
		LoadShader();
		LoadDiffuseTexture();
		LoadSpecularTexture();
		SetUseTexture();
	}

	void LoadShader()
	{
		std::string suffix = m_ShaderFilePath.substr(m_ShaderFilePath.find("."), m_ShaderFilePath.size() - 1);
		if (suffix != ".glsl")
			return;

		SAFE_DELETE_SET_NULL(m_Shader);
		m_Shader = new Shader(m_ShaderFilePath);
	}

	void LoadDiffuseTexture()
	{
		SAFE_DELETE_SET_NULL(m_DiffuseTexture);
		m_DiffuseTexture = new Texture(m_DiffuseTextureFilePath);
	}

	void LoadSpecularTexture()
	{
		SAFE_DELETE_SET_NULL(m_SpecularTexture);
		m_SpecularTexture = new Texture(m_SpecularTextureFilePath);
	}

	void SetUseTexture()
	{
		if (m_Shader)
		{
			//m_Shader->Bind();
			//m_Shader->SetInteger1("u_useTexture", m_UseTexture);
		}
	}

	MaterialComponent() = default;
	MaterialComponent(const MaterialComponent&) = default;

	void UnLoad()
	{
		SAFE_DELETE_SET_NULL(m_Shader);
		SAFE_DELETE_SET_NULL(m_DiffuseTexture);
		SAFE_DELETE_SET_NULL(m_SpecularTexture);
	}
};

//only store the projectmatrix
struct CameraComponent
{
	glm::mat4 m_ProjectMatrix{ 1.0f };
	float m_MoveSpeed = 10.0f;
	bool m_EnableWireframe = false;

	float m_Fovy = 60.0f;
	float m_Aspect = 1.0f;
	float m_NearZ = 1.0f;
	float m_FarZ = 1000.0f;

	void ReCalculateProjectMatrix()
	{
		m_ProjectMatrix = glm::perspective<float>(glm::radians(m_Fovy), m_Aspect, m_NearZ, m_FarZ);
	}

	void InitStateByAllProperty()
	{
		ReCalculateProjectMatrix();
		if (m_EnableWireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	CameraComponent() = default;
	CameraComponent(const CameraComponent&) = default;

};

//skybox 
struct SkyBoxComponent
{
	std::string m_ShaderFilePath;
	std::vector<std::string> m_TexturePaths;
	
	Shader* m_Shader{ nullptr };
	SkyBoxTexture* m_SkyBoxTexture{ nullptr };

	void Load()
	{
		m_Shader = new Shader(m_ShaderFilePath);
		m_SkyBoxTexture = new SkyBoxTexture(m_TexturePaths);
	}

	SkyBoxComponent() = default;

	void UnLoad()
	{
		SAFE_DELETE_SET_NULL(m_SkyBoxTexture);
		SAFE_DELETE_SET_NULL(m_Shader);
	}
};

//physics2d
struct RigidBody2DComponent
{
	enum class BodyType
	{
		Static = 0 ,
		Kinematic,
		Dynamic 
	};
	
	BodyType m_BodyType = BodyType::Static;
	bool m_FixedRotation = false;

	void* m_RuntimeBody = nullptr;


	RigidBody2DComponent() = default;
	RigidBody2DComponent(const RigidBody2DComponent&) = default;
};

struct BoxCollider2DComponent
{
	glm::vec2 m_Offset{ 0.0f, 0.0f };
	glm::vec2 m_Size{ 0.5f, 0.5f };
	
	float m_Density = 1.0f;
	float m_Friction = 0.5f;
	float m_Restitution = 0.0f;
	float m_RestitutionThreshold = 0.5f;

	void* m_RuntimeFixture = nullptr;

	BoxCollider2DComponent() = default;
	BoxCollider2DComponent(const BoxCollider2DComponent&) = default;
};


//physics 3d
struct RigidBodyComponent
{
	enum ColliderShape
	{
		Box = 0,
		Sphere,
	};
	static std::string ColliderShapeToString(ColliderShape colliderShape)
	{
		switch (colliderShape)
		{
		case Box:
			return "Box";
		case Sphere:
			return "Sphere";
		default:
			return "";
		}
	}
	static ColliderShape ColliderShapeFromString(const std::string& colliderShape)
	{
		if (colliderShape == "Box")
			return ColliderShape::Box;
		if (colliderShape == "Sphere")
			return ColliderShape::Sphere;
		return ColliderShape::Box;
	}

	ColliderShape m_ColliderShape = ColliderShape::Box;
	float m_Mass = 0;
	float m_Friction = 0.5;
	float m_Restitution = 0.5;
	bool m_ShowColliderShape = false;

	//Box Collider Shape Property
	glm::vec3 m_Offset{ 0.5f };

	//Sphere Collider Shape Property
	float m_Radius = 1.0f;

	void* m_RigidBody{ nullptr };
	RigidBodyComponent() = default;
	RigidBodyComponent(const RigidBodyComponent&) = default;
};


//Model Component
struct ModelComponent
{
	std::vector<MeshComponent> m_Mesh;
	std::vector<MaterialComponent> m_Material;

	std::string m_ModelFilePath{ "" };

	void Load()
	{
		UnLoad();
		m_Mesh.clear();
		m_Material.clear();

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(m_ModelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs 
			| aiProcess_GenNormals | aiProcess_GenBoundingBoxes | aiProcess_GenUVCoords);


		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG_ERROR("ERROR::ASSIMP::" + importer.GetErrorString());
			return;
		}
		
		ProcessNode(scene->mRootNode, scene);
	}


	void UnLoad()
	{
		for (auto& meshc : m_Mesh)
		{
			meshc.UnLoad();
		}

		for (auto& matc : m_Material)
		{
			matc.UnLoad();
		}
	}
private:
	void ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			ProcessMesh(mesh, scene);
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	void ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		MeshComponent meshc;
		MaterialComponent matc;

		//vertex
		std::vector<MeshComponent::VertexPosTex> vertexData;
		MeshComponent::VertexPosTex tmpVertexPosTex;
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

			vertexData.push_back(tmpVertexPosTex);
		}

		//index
		std::vector<unsigned int> indexData;
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
			{
				indexData.push_back(mesh->mFaces[i].mIndices[j]);
			}
		}

		meshc.Load(vertexData.data(), (unsigned int)vertexData.size(), indexData.data(), (unsigned int)indexData.size());


		//material
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		aiString textureFilepath;
		
		material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilepath);
		matc.m_DiffuseTextureFilePath = std::string(textureFilepath.C_Str()) == "" ? "assets/textures/white_background.jpeg" : m_ModelFilePath.substr(0, m_ModelFilePath.find_last_of('/')) + "/" + textureFilepath.C_Str();

		material->GetTexture(aiTextureType_SPECULAR, 0, &textureFilepath);
		matc.m_SpecularTextureFilePath = std::string(textureFilepath.C_Str()) == "" ? "assets/textures/white_background.jpeg" : m_ModelFilePath.substr(0, m_ModelFilePath.find_last_of('/')) + "/" + textureFilepath.C_Str();
		matc.m_UseTexture = true;

		aiColor4D color;

		material->Get(AI_MATKEY_COLOR_AMBIENT, color);
		matc.m_Ambient = glm::vec4(color.r, color.g, color.b, color.a);

		material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		matc.m_Diffuse = glm::vec4(color.r, color.g, color.b, color.a);

		material->Get(AI_MATKEY_COLOR_SPECULAR, color);
		matc.m_Specular = glm::vec4(color.r, color.g, color.b, color.a);

		matc.Load();

		m_Mesh.push_back(meshc);
		m_Material.push_back(matc);
	}
public:
	ModelComponent() = default;
	ModelComponent(const ModelComponent&) = default;
};


////skeleton
//struct SkeletonMeshComponent
//{
//	struct VertexPosTex
//	{
//		glm::vec3 position;
//		glm::vec3 normal;
//		glm::vec2 texcoord;
//		glm::ivec4 boneIds{-1};
//		glm::vec4 weights{ -1.0f};
//	};
//
//	VertexArray* m_VertexArray{ nullptr };
//	VertexBuffer* m_Vertexbuffer{ nullptr };
//	IndexBuffer* m_Indexbuffer{ nullptr };
//
//	std::string m_MeshFilePath{ "" };
//
//	SkeletonMeshComponent() = default;
//	SkeletonMeshComponent(const SkeletonMeshComponent&) = default;
//
//	//load mesh by m_MeshFilePath
//	void Load()
//	{
//		auto pos = m_MeshFilePath.find(".");
//		if (pos == std::string::npos)
//			return;
//		std::string suffix = m_MeshFilePath.substr(pos, m_MeshFilePath.size() - 1);
//		if (suffix != ".mesh")
//			return;
//
//		Enternity::Blob blob2(DEFAULT_BLOB_LENGTH);
//		if (!Enternity::FileOperation::ReadFile(blob2, m_MeshFilePath))
//			return;
//
//		UnLoad();
//		unsigned int vertexcount2;
//		unsigned int indexcount2;
//		memcpy_s(&vertexcount2, sizeof(unsigned int), blob2.GetData(), sizeof(unsigned int));
//		memcpy_s(&indexcount2, sizeof(unsigned int), (char*)blob2.GetData() + sizeof(unsigned int), sizeof(unsigned int));
//
//		VertexPosTex* vpt = new VertexPosTex[vertexcount2];
//		unsigned int* indices2 = new unsigned int[indexcount2];
//		memcpy_s(vpt, vertexcount2 * sizeof(VertexPosTex), (char*)blob2.GetData() + 2 * sizeof(unsigned int), vertexcount2 * sizeof(VertexPosTex));
//		memcpy_s(indices2, indexcount2 * sizeof(unsigned int), (char*)blob2.GetData() + 2 * sizeof(unsigned int) + vertexcount2 * sizeof(VertexPosTex), indexcount2 * sizeof(unsigned int));
//
//
//		m_Vertexbuffer = new VertexBuffer(vpt, vertexcount2 * sizeof(VertexPosTex));
//		m_VertexArray = new VertexArray;
//		VertexBufferLayout  vertexBufferLayout;
//		vertexBufferLayout.Push({ 0, 3, GL_FLOAT, false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 0 });
//		vertexBufferLayout.Push({ 1, 3, GL_FLOAT, false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 3 * sizeof(float) });
//		vertexBufferLayout.Push({ 2, 2, GL_FLOAT, false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 6 * sizeof(float) });
//		vertexBufferLayout.Push({ 3, 4, GL_INT,   false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 8 * sizeof(float) });
//		vertexBufferLayout.Push({ 4, 4, GL_FLOAT, false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 8 * sizeof(float) + 4 * sizeof(unsigned int) });
//		m_VertexArray->Add(*m_Vertexbuffer, vertexBufferLayout);
//		m_Indexbuffer = new IndexBuffer(indices2, indexcount2);
//
//		delete[] vpt;
//		delete[] indices2;
//	}
//
//	//load by data
//	void Load(const void* vertexData, unsigned int vertexCount, const unsigned int* indexData, unsigned int indexCount)
//	{
//		m_Vertexbuffer = new VertexBuffer(vertexData, vertexCount * sizeof(VertexPosTex));
//		m_VertexArray = new VertexArray;
//		VertexBufferLayout  vertexBufferLayout;
//		vertexBufferLayout.Push({ 0, 3, GL_FLOAT, false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 0 });
//		vertexBufferLayout.Push({ 1, 3, GL_FLOAT, false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 3 * sizeof(float) });
//		vertexBufferLayout.Push({ 2, 2, GL_FLOAT, false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 6 * sizeof(float) });
//		vertexBufferLayout.Push({ 3, 4, GL_INT,   false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 8 * sizeof(float) });
//		vertexBufferLayout.Push({ 4, 4, GL_FLOAT, false,  12 * sizeof(float) + 4 * sizeof(unsigned int), 8 * sizeof(float) + 4 * sizeof(unsigned int) });
//		m_VertexArray->Add(*m_Vertexbuffer, vertexBufferLayout);
//		m_Indexbuffer = new IndexBuffer(indexData, indexCount);
//	}
//
//	void UnLoad()
//	{
//		SAFE_DELETE_SET_NULL(m_VertexArray);
//		SAFE_DELETE_SET_NULL(m_Vertexbuffer);
//		SAFE_DELETE_SET_NULL(m_Indexbuffer);
//	}
//};



//struct SkeletonModelComponent
//{
//	std::vector<SkeletonMeshComponent> m_Mesh;
//	std::vector<MaterialComponent> m_Material;
//
//	std::string m_ModelFilePath{ "" };
//
//	struct BoneInfo
//	{
//		glm::mat4 OffsetMatrix;
//		glm::mat4 TranformMatrix;
//		glm::mat4 FinalMatrix{ 1.0f };
//		std::string m_name;
//	};
//	std::map<std::string, int> m_BoneNameToIndex;
//
//	std::vector<BoneInfo> m_Bones;
//
//	void Load()
//	{
//		UnLoad();
//		m_Mesh.clear();
//		m_Material.clear();
//
//		Assimp::Importer importer;
//		const aiScene* scene = importer.ReadFile(m_ModelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs
//			| aiProcess_GenNormals | aiProcess_GenBoundingBoxes | aiProcess_GenUVCoords);
//
//
//		if (!scene || /*scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||*/ !scene->mRootNode)
//		{
//			LOG_ERROR("ERROR::ASSIMP::" + importer.GetErrorString());
//			return;
//		}
//
//		//ProcessNode(scene->mRootNode, scene);
//
//		ReadNodeHierarchy(scene->mRootNode, glm::mat4(1.0f));
//
//		ProcessFinalTransform();
//		int i = 0;
//		i++;
//	}
//
//
//	void UnLoad()
//	{
//		for (auto& meshc : m_Mesh)
//		{
//			meshc.UnLoad();
//		}
//
//		for (auto& matc : m_Material)
//		{
//			matc.UnLoad();
//		}
//	}
//private:
//	void ReadNodeHierarchy(aiNode* node, const glm::mat4& parentTransform)
//	{
//		if (m_BoneNameToIndex.find(node->mName.C_Str()) == m_BoneNameToIndex.end())
//		{
//			BoneInfo boneInfo;
//			boneInfo.m_name = node->mName.C_Str();
//			boneInfo.TranformMatrix = parentTransform * AssimpMat4ToGlmMat4(node->mTransformation);
//			m_Bones.push_back(boneInfo);
//
//			m_BoneNameToIndex.insert({ boneInfo.m_name, m_Bones.size() - 1});
//			for (unsigned int i = 0; i < node->mNumChildren; i++)
//			{
//				ReadNodeHierarchy(node->mChildren[i], boneInfo.TranformMatrix);
//			}
//		}
//	}
//
//	glm::mat4 AssimpMat4ToGlmMat4(const aiMatrix4x4& aiMat4)
//	{
//		return glm::mat4{
//			aiMat4.a1, aiMat4.a2, aiMat4.a3, aiMat4.a4,
//			aiMat4.b1, aiMat4.b2, aiMat4.b3, aiMat4.b4,
//			aiMat4.c1, aiMat4.c2, aiMat4.c3, aiMat4.c4,
//			aiMat4.d1, aiMat4.d2, aiMat4.d3, aiMat4.d4,
//		};
//	}
//
//	glm::mat4 CalGlobalTransform(aiNode* selfNode)
//	{
//		std::vector<glm::mat4> matPath;
//
//		while (selfNode)
//		{
//			matPath.emplace_back(AssimpMat4ToGlmMat4(selfNode->mTransformation));
//			selfNode = selfNode->mParent;
//		}
//		glm::mat4 res = matPath[matPath.size() -1];
//		for (int i = matPath.size() - 2; i >= 0; i--)
//		{
//			res *= matPath[i];
//		}
//
//		return res;
//	}
//
//	void ProcessFinalTransform()
//	{
//		//for (int i = 0; i < m_Mesh.size(); i++)
//		//{
//		//	auto& bones = m_Mesh[i].m_Bones;
//		//	for (auto& bone : bones)
//		//	{
//		//		bone.FinalMatrix = CalGlobalTransform(bone.m_Node) * bone.OffsetMatrix;
//		//	}
//		//}
//		
//	}
//
//	void ProcessNode(aiNode* node, const aiScene* scene)
//	{
//		for (unsigned int i = 0; i < node->mNumMeshes; i++)
//		{
//			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//			ProcessMesh(mesh, scene, node);
//		}
//
//		for (unsigned int i = 0; i < node->mNumChildren; i++)
//		{
//			ProcessNode(node->mChildren[i], scene);
//		}
//	}
//
//	void ProcessMesh(aiMesh* mesh, const aiScene* scene, aiNode* node)
//	{
//		SkeletonMeshComponent meshc;
//		MaterialComponent matc;
//		matc.m_ShaderFilePath = "assets/shaders/SkeletonModel.glsl";
//
//		//vertex
//		std::vector<SkeletonMeshComponent::VertexPosTex> vertexData;
//		SkeletonMeshComponent::VertexPosTex tmpVertexPosTex;
//		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
//		{
//			//position
//			tmpVertexPosTex.position.x = mesh->mVertices[i].x;
//			tmpVertexPosTex.position.y = mesh->mVertices[i].y;
//			tmpVertexPosTex.position.z = mesh->mVertices[i].z;
//
//			//normal
//			tmpVertexPosTex.normal.x = mesh->mNormals[i].x;
//			tmpVertexPosTex.normal.y = mesh->mNormals[i].y;
//			tmpVertexPosTex.normal.z = mesh->mNormals[i].z;
//
//			//texcoord
//			if (mesh->HasTextureCoords(0))
//			{
//				tmpVertexPosTex.texcoord.x = mesh->mTextureCoords[0][i].x;
//				tmpVertexPosTex.texcoord.y = -mesh->mTextureCoords[0][i].y + 1;
//			}
//
//			vertexData.push_back(tmpVertexPosTex);
//		}
//
//		//index
//		std::vector<unsigned int> indexData;
//		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
//		{
//			for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
//			{
//				indexData.push_back(mesh->mFaces[i].mIndices[j]);
//			}
//		}
//
//		LOG_INFO("Mesh Name: " + mesh->mName.C_Str() + ", Vertex Count: " + std::to_string(vertexData.size()) + ", Index Count: " + std::to_string(indexData.size()));
//		//skeleton
//		LOG_DEBUG("This mesh has " + std::to_string(mesh->mNumBones) + " bones");
//		for (unsigned int i = 0; i < mesh->mNumBones; i++)
//		{
//			aiBone* bone = mesh->mBones[i];
//			//SkeletonMeshComponent::BoneInfo boneInfo;
//			//boneInfo.OffsetMatrix = AssimpMat4ToGlmMat4(bone->mOffsetMatrix);
//			//boneInfo.m_Node = node;
//			//boneInfo.m_name = bone->mName.C_Str();
//			//meshc.m_Bones.push_back(boneInfo);
//			
//			LOG_DEBUG(std::to_string(i) + " : " + bone->mName.C_Str() + ", affect " + std::to_string(bone->mNumWeights) + " vertices");
//			for (unsigned int j = 0; j < bone->mNumWeights; j++)
//			{
//				LOG_WARN(std::to_string(j) + " : " + "vertexid: " + std::to_string(bone->mWeights[j].mVertexId) + " weight: " + std::to_string(bone->mWeights[j].mWeight));
//
//				if (vertexData[bone->mWeights[j].mVertexId].boneIds.x == -1 && vertexData[bone->mWeights[j].mVertexId].weights.x == -1)
//				{
//					vertexData[bone->mWeights[j].mVertexId].boneIds.x = i;
//					vertexData[bone->mWeights[j].mVertexId].weights.x = bone->mWeights[j].mWeight;
//					continue;
//				}
//				if (vertexData[bone->mWeights[j].mVertexId].boneIds.y == -1 && vertexData[bone->mWeights[j].mVertexId].weights.y == -1)
//				{
//					vertexData[bone->mWeights[j].mVertexId].boneIds.y = i;
//					vertexData[bone->mWeights[j].mVertexId].weights.y = bone->mWeights[j].mWeight;
//					continue;
//				}
//				if (vertexData[bone->mWeights[j].mVertexId].boneIds.z == -1 && vertexData[bone->mWeights[j].mVertexId].weights.z == -1)
//				{
//					vertexData[bone->mWeights[j].mVertexId].boneIds.z = i;
//					vertexData[bone->mWeights[j].mVertexId].weights.z = bone->mWeights[j].mWeight;
//					continue;
//				}
//				if (vertexData[bone->mWeights[j].mVertexId].boneIds.w == -1 && vertexData[bone->mWeights[j].mVertexId].weights.w == -1)
//				{
//					vertexData[bone->mWeights[j].mVertexId].boneIds.w = i;
//					vertexData[bone->mWeights[j].mVertexId].weights.w = bone->mWeights[j].mWeight;
//				}
//			}
//		}
//
//		meshc.Load(vertexData.data(), (unsigned int)vertexData.size(), indexData.data(), (unsigned int)indexData.size());
//
//		//material
//		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
//		aiString textureFilepath;
//
//		material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilepath);
//		matc.m_DiffuseTextureFilePath = std::string(textureFilepath.C_Str()) == "" ? "assets/textures/white_background.jpeg" : m_ModelFilePath.substr(0, m_ModelFilePath.find_last_of('/')) + "/" + textureFilepath.C_Str();
//
//		material->GetTexture(aiTextureType_SPECULAR, 0, &textureFilepath);
//		matc.m_SpecularTextureFilePath = std::string(textureFilepath.C_Str()) == "" ? "assets/textures/white_background.jpeg" : m_ModelFilePath.substr(0, m_ModelFilePath.find_last_of('/')) + "/" + textureFilepath.C_Str();
//		matc.m_UseTexture = true;
//
//		aiColor4D color;
//
//		material->Get(AI_MATKEY_COLOR_AMBIENT, color);
//		matc.m_Ambient = glm::vec4(color.r, color.g, color.b, color.a);
//
//		material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
//		matc.m_Diffuse = glm::vec4(color.r, color.g, color.b, color.a);
//
//		material->Get(AI_MATKEY_COLOR_SPECULAR, color);
//		matc.m_Specular = glm::vec4(color.r, color.g, color.b, color.a);
//
//		matc.Load();
//
//		m_Mesh.push_back(meshc);
//		m_Material.push_back(matc);
//	}
//public:
//	SkeletonModelComponent() = default;
//	SkeletonModelComponent(const SkeletonModelComponent&) = default;
//};
END_ENTERNITY