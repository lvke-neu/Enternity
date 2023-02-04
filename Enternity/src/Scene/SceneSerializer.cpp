#include "SceneSerializer.h"
#include "SceneManager.h"
#include "Imgui/ImguiManager.h"
#include "File/FileOperation.h"
#include "Log/Log.h"
#include "Scene/ECS/Component/SkeletonModelComponent.h"

namespace YAML {

	template<>
	struct convert<glm::vec2>
	{
		static Node encode(const glm::vec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

	template<>
	struct convert<Enternity::MaterialComponent>
	{
		static Node encode(const Enternity::MaterialComponent& matc)
		{
			Node node;
			node.push_back(matc.m_Ambient);
			node.push_back(matc.m_Diffuse);
			node.push_back(matc.m_Specular);
			node.push_back(matc.m_DiffuseTextureFilePath);
			node.push_back(matc.m_ShaderFilePath);
			node.push_back(matc.m_Shininess);
			node.push_back(matc.m_SpecularTextureFilePath);
			
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, Enternity::MaterialComponent& matc)
		{
			if (!node.IsSequence() || node.size() != 7)
				return false;

			matc.m_Ambient = node[0].as<glm::vec4>();
			matc.m_Diffuse = node[1].as<glm::vec4>();
			matc.m_Specular = node[2].as<glm::vec4>();
			matc.m_DiffuseTextureFilePath = node[3].as<std::string>();
			matc.m_ShaderFilePath = node[4].as<std::string>();
			matc.m_Shininess = node[5].as<float>();
			matc.m_SpecularTextureFilePath = node[6].as<std::string>();

			matc.Load();

			return true;
		}
	};
}

BEGIN_ENTERNITY

static YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v)
{
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
	return out;
}

static YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
{
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
	return out;
}

static YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
{
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
	return out;
}

static YAML::Emitter& operator<<(YAML::Emitter& out, const Enternity::MaterialComponent& matc)
{
	out << YAML::Flow;
	out << YAML::BeginSeq << matc.m_Ambient 
		<< matc.m_Diffuse
		<< matc.m_Specular
		<<matc.m_DiffuseTextureFilePath
		<<matc.m_ShaderFilePath
		<<matc.m_Shininess
		<<matc.m_SpecularTextureFilePath
		<< YAML::EndSeq;
	return out;
}

void SceneSerializer::SerializeEntity(YAML::Emitter& out, Entity entity)
{
	out << YAML::BeginMap;
	out << YAML::Key << "Entity" << YAML::Value << entity.GetEntityUid();

	if (entity.HasComponent<TagComponent>())
	{
		out << YAML::Key << "TagComponent";
		out << YAML::BeginMap;
		auto& tagComponent = entity.GetComponent<TagComponent>();
		out << YAML::Key << "m_Tag" << YAML::Value << tagComponent.m_Tag;
		out << YAML::EndMap;
	}
	
	if (entity.HasComponent<CameraComponent>())
	{
		out << YAML::Key << "CameraComponent";
		out << YAML::BeginMap;
		auto& cameraComponent = entity.GetComponent<CameraComponent>();
		out << YAML::Key << "m_MoveSpeed" << YAML::Value << cameraComponent.m_MoveSpeed;
		out << YAML::Key << "m_EnableWireframe" << YAML::Value << cameraComponent.m_EnableWireframe;
		out << YAML::Key << "m_Fovy" << YAML::Value << cameraComponent.m_Fovy;
		//out << YAML::Key << "m_Aspect" << YAML::Value << cameraComponent.m_Aspect;
		out << YAML::Key << "m_NearZ" << YAML::Value << cameraComponent.m_NearZ;
		out << YAML::Key << "m_FarZ" << YAML::Value << cameraComponent.m_FarZ;
		out << YAML::EndMap;
	}

	if (entity.HasComponent<TransformComponent>())
	{
		out << YAML::Key << "TransformComponent";
		out << YAML::BeginMap;
		auto& transformComponent = entity.GetComponent<TransformComponent>();
		out << YAML::Key << "m_Translation" << YAML::Value << transformComponent.m_Translation;
		out << YAML::Key << "m_Rotation" << YAML::Value << transformComponent.m_Rotation;
		out << YAML::Key << "m_Scale" << YAML::Value << transformComponent.m_Scale;
		out << YAML::EndMap;
	}

	if (entity.HasComponent<MeshComponent>())
	{
		out << YAML::Key << "MeshComponent";
		out << YAML::BeginMap;
		auto& meshComponent = entity.GetComponent<MeshComponent>();
		out << YAML::Key << "m_MeshFilePath" << YAML::Value << meshComponent.m_MeshFilePath;
		out << YAML::EndMap;
	}

	if (entity.HasComponent<MaterialComponent>())
	{
		out << YAML::Key << "MaterialComponent";
		out << YAML::BeginMap;
		auto& materialComponent = entity.GetComponent<MaterialComponent>();
		out << YAML::Key << "m_ShaderFilePath" << YAML::Value << materialComponent.m_ShaderFilePath;
		out << YAML::Key << "m_DiffuseTextureFilePath" << YAML::Value << materialComponent.m_DiffuseTextureFilePath;
		out << YAML::Key << "m_SpecularTextureFilePath" << YAML::Value << materialComponent.m_SpecularTextureFilePath;
		out << YAML::Key << "m_UseTexture" << YAML::Value << materialComponent.m_UseTexture;
		out << YAML::Key << "m_Ambient" << YAML::Value << materialComponent.m_Ambient;
		out << YAML::Key << "m_Diffuse" << YAML::Value << materialComponent.m_Diffuse;
		out << YAML::Key << "m_Specular" << YAML::Value << materialComponent.m_Specular;
		out << YAML::Key << "m_Shininess" << YAML::Value << materialComponent.m_Shininess;
		out << YAML::EndMap;
	}

	if (entity.HasComponent<RigidBody2DComponent>())
	{
		out << YAML::Key << "RigidBody2DComponent";
		out << YAML::BeginMap;
		auto& rigidBody2DComponent = entity.GetComponent<RigidBody2DComponent>();
		out << YAML::Key << "m_BodyType" << YAML::Value << (int)rigidBody2DComponent.m_BodyType;
		out << YAML::Key << "m_FixedRotation" << YAML::Value << rigidBody2DComponent.m_FixedRotation;
		out << YAML::EndMap;
	}

	if (entity.HasComponent<BoxCollider2DComponent>())
	{
		out << YAML::Key << "BoxCollider2DComponent";
		out << YAML::BeginMap;
		auto& boxCollider2DComponent = entity.GetComponent<BoxCollider2DComponent>();
		out << YAML::Key << "m_Offset" << YAML::Value << boxCollider2DComponent.m_Offset;
		out << YAML::Key << "m_Size" << YAML::Value << boxCollider2DComponent.m_Size;
		out << YAML::Key << "m_Density" << YAML::Value << boxCollider2DComponent.m_Density;
		out << YAML::Key << "m_Friction" << YAML::Value << boxCollider2DComponent.m_Friction;
		out << YAML::Key << "m_Restitution" << YAML::Value << boxCollider2DComponent.m_Restitution;
		out << YAML::Key << "m_RestitutionThreshold" << YAML::Value << boxCollider2DComponent.m_RestitutionThreshold;
		out << YAML::EndMap;
	}

	if (entity.HasComponent<RigidBodyComponent>())
	{
		out << YAML::Key << "RigidBodyComponent";
		out << YAML::BeginMap;
		auto& rigidBodyComponent = entity.GetComponent<RigidBodyComponent>();
		out << YAML::Key << "m_ColliderShape" << YAML::Value << RigidBodyComponent::ColliderShapeToString(rigidBodyComponent.m_ColliderShape);
		out << YAML::Key << "m_Mass" << YAML::Value << rigidBodyComponent.m_Mass;
		out << YAML::Key << "m_Friction" << YAML::Value << rigidBodyComponent.m_Friction;
		out << YAML::Key << "m_Restitution" << YAML::Value << rigidBodyComponent.m_Restitution;
		out << YAML::Key << "m_ShowColliderShape" << YAML::Value << rigidBodyComponent.m_ShowColliderShape;
		out << YAML::Key << "m_Offset" << YAML::Value << rigidBodyComponent.m_Offset;
		out << YAML::Key << "m_Radius" << YAML::Value << rigidBodyComponent.m_Radius;
		out << YAML::EndMap;
	}

	if (entity.HasComponent<ModelComponent>())
	{
		out << YAML::Key << "ModelComponent";
		out << YAML::BeginMap;
		auto& modelc = entity.GetComponent<ModelComponent>();
		out << YAML::Key << "m_ModelFilePath" << YAML::Value << modelc.m_ModelFilePath;
		out << YAML::Key << "m_Material" << YAML::Value << modelc.m_Material;
		out << YAML::EndMap;
	}

	if (entity.HasComponent<MotorComponent>())
	{
		out << YAML::Key << "MotorComponent";
		out << YAML::BeginMap;
		auto& motorComponent = entity.GetComponent<MotorComponent>();
		out << YAML::Key << "m_RotationXAnglePerSecond" << YAML::Value << motorComponent.m_RotationXAnglePerSecond;
		out << YAML::Key << "m_RotationYAnglePerSecond" << YAML::Value << motorComponent.m_RotationYAnglePerSecond;
		out << YAML::EndMap;
	}

	out << YAML::EndMap;
}

void SceneSerializer::Serialize(const std::string& filePath)
{
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "Scene" << YAML::Value << "Untitled";
	out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
	
	SerializeEntity(out, SceneManager::GetInstance().m_EditorCameraEntity);
	SerializeEntity(out, SceneManager::GetInstance().m_PlayerCameraEntity);
	SerializeEntity(out, SceneManager::GetInstance().m_DirectionLightEntity);

	for (auto& entity : SceneManager::GetInstance().m_Entities)
	{
		SerializeEntity(out, entity.second);
	}
	
	out << YAML::EndSeq;
	out << YAML::EndMap;

	out.c_str();

	Blob blob((unsigned int)out.size());
	memcpy_s(blob.GetData(), blob.GetLength(), out.c_str(), blob.GetLength());

	FileOperation::WriteFile(blob, filePath);
}

bool SceneSerializer::Deserialize(const std::string& filePath)
{
	if (filePath == "")
		return false;
	std::string suffix = filePath.substr(filePath.find("."), filePath.size() - 1);
	if (suffix != ".scene")
		return false;

	YAML::Node data;
	try
	{
		data = YAML::LoadFile(filePath);
	}
	catch (std::exception e)
	{
		LOG_ERROR("Failed to load scene file, " + e.what());
		return false;
	}


	if (!data["Scene"])
		return false;

	ImguiManager::GetInstance().GetSceneHierarchyPanel()->SetSelectedEntityNull();
	SceneManager::GetInstance().Clear();
	auto entities = data["Entities"];
	if (entities)
	{
		int index = 1;
		for (auto entity : entities)
		{
			auto cameraComponent = entity["CameraComponent"];
			auto cameraTransformComponent = entity["TransformComponent"];
			if (index == 1 &&cameraComponent && cameraTransformComponent)
			{
				auto& mainCameraEntity = SceneManager::GetInstance().m_EditorCameraEntity;
				auto& cc = mainCameraEntity.GetComponent<CameraComponent>();
				cc.m_MoveSpeed = cameraComponent["m_MoveSpeed"].as<float>();
				cc.m_EnableWireframe = cameraComponent["m_EnableWireframe"].as<bool>();
				cc.m_Fovy = cameraComponent["m_Fovy"].as<float>();
				//cc.m_Aspect = cameraComponent["m_Aspect"].as<float>();
				cc.m_NearZ = cameraComponent["m_NearZ"].as<float>();
				cc.m_FarZ = cameraComponent["m_FarZ"].as<float>();
				cc.InitStateByAllProperty();
				auto& tc = mainCameraEntity.GetComponent<TransformComponent>();
				tc.m_Translation = cameraTransformComponent["m_Translation"].as<glm::vec3>();
				tc.m_Rotation = cameraTransformComponent["m_Rotation"].as<glm::vec3>();
				tc.m_Scale = cameraTransformComponent["m_Scale"].as<glm::vec3>();

				index++;
				continue;
			}

			if (index == 2 && cameraComponent && cameraTransformComponent)
			{
				auto& mainCameraEntity = SceneManager::GetInstance().m_PlayerCameraEntity;
				auto& cc = mainCameraEntity.GetComponent<CameraComponent>();
				cc.m_MoveSpeed = cameraComponent["m_MoveSpeed"].as<float>();
				cc.m_EnableWireframe = cameraComponent["m_EnableWireframe"].as<bool>();
				cc.m_Fovy = cameraComponent["m_Fovy"].as<float>();
				//cc.m_Aspect = cameraComponent["m_Aspect"].as<float>();
				cc.m_NearZ = cameraComponent["m_NearZ"].as<float>();
				cc.m_FarZ = cameraComponent["m_FarZ"].as<float>();
				cc.InitStateByAllProperty();
				auto& tc = mainCameraEntity.GetComponent<TransformComponent>();
				tc.m_Translation = cameraTransformComponent["m_Translation"].as<glm::vec3>();
				tc.m_Rotation = cameraTransformComponent["m_Rotation"].as<glm::vec3>();
				tc.m_Scale = cameraTransformComponent["m_Scale"].as<glm::vec3>();

				index++;
				continue;
			}

			if (index == 3)
			{
				auto& directionLightEntity = SceneManager::GetInstance().m_DirectionLightEntity;

				auto transformComponent = entity["TransformComponent"];
				if (transformComponent)
				{
					auto& tc = directionLightEntity.GetComponent<TransformComponent>();
					tc.m_Translation = transformComponent["m_Translation"].as<glm::vec3>();
					tc.m_Rotation = transformComponent["m_Rotation"].as<glm::vec3>();
					tc.m_Scale = transformComponent["m_Scale"].as<glm::vec3>();
				}

				auto meshComponent = entity["MeshComponent"];
				if (meshComponent)
				{
					auto& mc = directionLightEntity.GetComponent<MeshComponent>();
					mc.m_MeshFilePath = meshComponent["m_MeshFilePath"].as<std::string>();
					mc.Load();
				}

				auto materialComponent = entity["MaterialComponent"];
				if (materialComponent)
				{
					auto& mc = directionLightEntity.GetComponent<MaterialComponent>();
					mc.m_ShaderFilePath = materialComponent["m_ShaderFilePath"].as<std::string>();
					mc.m_DiffuseTextureFilePath = materialComponent["m_DiffuseTextureFilePath"].as<std::string>();
					mc.m_SpecularTextureFilePath = materialComponent["m_SpecularTextureFilePath"].as<std::string>();
					mc.m_UseTexture = materialComponent["m_UseTexture"].as<bool>();
					mc.m_Ambient = materialComponent["m_Ambient"].as<glm::vec4>();
					mc.m_Diffuse = materialComponent["m_Diffuse"].as<glm::vec4>();
					mc.m_Specular = materialComponent["m_Specular"].as<glm::vec4>();
					mc.m_Shininess = materialComponent["m_Shininess"].as<float>();
					mc.Load();
				}

				index++;
				continue;
			}


			Entity deserializeEntity(&SceneManager::GetInstance().m_Registry);
			
			auto tagComponent = entity["TagComponent"];
			if (tagComponent)
			{
				deserializeEntity.GetComponent<TagComponent>().m_Tag = tagComponent["m_Tag"].as<std::string>();
			}

			auto transformComponent = entity["TransformComponent"];
			if (transformComponent)
			{
				auto& tc = deserializeEntity.AddComponent<TransformComponent>();
				tc.m_Translation = transformComponent["m_Translation"].as<glm::vec3>();
				tc.m_Rotation = transformComponent["m_Rotation"].as<glm::vec3>();
				tc.m_Scale = transformComponent["m_Scale"].as<glm::vec3>();
			}

			auto meshComponent = entity["MeshComponent"];
			if (meshComponent)
			{
				auto& mc = deserializeEntity.AddComponent<MeshComponent>();
				mc.m_MeshFilePath = meshComponent["m_MeshFilePath"].as<std::string>();
				mc.Load();
			}

			auto materialComponent = entity["MaterialComponent"];
			if (materialComponent)
			{
				auto& mc = deserializeEntity.AddComponent<MaterialComponent>();
				
				mc.m_ShaderFilePath = materialComponent["m_ShaderFilePath"].as<std::string>();
				mc.m_DiffuseTextureFilePath = materialComponent["m_DiffuseTextureFilePath"].as<std::string>();
				mc.m_SpecularTextureFilePath = materialComponent["m_SpecularTextureFilePath"].as<std::string>();
				mc.m_UseTexture = materialComponent["m_UseTexture"].as<bool>();
				mc.m_Ambient = materialComponent["m_Ambient"].as<glm::vec4>();
				mc.m_Diffuse = materialComponent["m_Diffuse"].as<glm::vec4>();
				mc.m_Specular = materialComponent["m_Specular"].as<glm::vec4>();
				mc.m_Shininess = materialComponent["m_Shininess"].as<float>();
				mc.Load();
			}

			auto motorComponent = entity["MotorComponent"];
			if (motorComponent)
			{
				auto& mc = deserializeEntity.AddComponent<MotorComponent>();
				mc.m_RotationXAnglePerSecond = motorComponent["m_RotationXAnglePerSecond"].as<float>();
				mc.m_RotationYAnglePerSecond = motorComponent["m_RotationYAnglePerSecond"].as<float>();
			}

			auto rigidBody2DComponent = entity["RigidBody2DComponent"];
			if (rigidBody2DComponent)
			{
				auto& rb2dc = deserializeEntity.AddComponent<RigidBody2DComponent>();
				rb2dc.m_BodyType = (RigidBody2DComponent::BodyType)rigidBody2DComponent["m_BodyType"].as<int>();
				rb2dc.m_FixedRotation = rigidBody2DComponent["m_FixedRotation"].as<bool>();
			}

			auto boxCollider2DComponent = entity["BoxCollider2DComponent"];
			if (boxCollider2DComponent)
			{
				auto& bc2dc = deserializeEntity.AddComponent<BoxCollider2DComponent>();
				bc2dc.m_Offset = boxCollider2DComponent["m_Offset"].as<glm::vec2>();
				bc2dc.m_Size = boxCollider2DComponent["m_Size"].as<glm::vec2>();
				bc2dc.m_Density = boxCollider2DComponent["m_Density"].as<float>();
				bc2dc.m_Friction = boxCollider2DComponent["m_Friction"].as<float>();
				bc2dc.m_Restitution = boxCollider2DComponent["m_Restitution"].as<float>();
				bc2dc.m_RestitutionThreshold = boxCollider2DComponent["m_RestitutionThreshold"].as<float>();
			}

			auto rigidBodyComponent = entity["RigidBodyComponent"];
			if (rigidBodyComponent)
			{
				auto& rbc = deserializeEntity.AddComponent<RigidBodyComponent>();
				rbc.m_ColliderShape =RigidBodyComponent::ColliderShapeFromString(rigidBodyComponent["m_ColliderShape"].as<std::string>());
				rbc.m_Offset = rigidBodyComponent["m_Offset"].as<glm::vec3>();
				rbc.m_Radius = rigidBodyComponent["m_Radius"].as<float>();
				rbc.m_Mass = rigidBodyComponent["m_Mass"].as<float>();
				rbc.m_Friction = rigidBodyComponent["m_Friction"].as<float>();
				rbc.m_Restitution = rigidBodyComponent["m_Restitution"].as<float>();
				rbc.m_ShowColliderShape = rigidBodyComponent["m_ShowColliderShape"].as<bool>();
			}

			auto modelComponent = entity["ModelComponent"];
			if (modelComponent)
			{
				auto& modelc = deserializeEntity.AddComponent<ModelComponent>();
				modelc.m_ModelFilePath = modelComponent["m_ModelFilePath"].as<std::string>();
				modelc.Load();
				modelc.m_Material = modelComponent["m_Material"].as<std::vector<MaterialComponent>>();
			}

			auto skeletonModelComponent = entity["SkeletonModelComponent"];
			if (skeletonModelComponent)
			{
				auto& smc = deserializeEntity.AddComponent<SkeletonModelComponent>();
				smc.m_ModelFilePath = skeletonModelComponent["m_ModelFilePath"].as<std::string>();
				smc.Load();
				//smc.m_Material = skeletonModelComponent["m_Material"].as<MaterialComponent>();
			}

			SceneManager::GetInstance().m_Entities.insert({ deserializeEntity.GetEntityUid(), deserializeEntity });
			LOG_INFO("Deserialize Entity:" + deserializeEntity.GetComponent<TagComponent>().m_Tag + " complete");
		}
	}

	return true;
}

END_ENTERNITY

