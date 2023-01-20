#include "SceneSerializer.h"
#include "SceneManager.h"
#include "Imgui/ImguiManager.h"
#include "File/FileOperation.h"
#include "Log/Log.h"


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
		out << YAML::Key << "m_TextureFilePath" << YAML::Value << materialComponent.m_TextureFilePath;
		out << YAML::Key << "m_ShaderFilePath" << YAML::Value << materialComponent.m_ShaderFilePath;
		out << YAML::Key << "m_bUseColor" << YAML::Value << materialComponent.m_bUseColor;
		out << YAML::Key << "m_BaseColor" << YAML::Value << materialComponent.m_BaseColor;
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
				mc.m_TextureFilePath = materialComponent["m_TextureFilePath"].as<std::string>();
				mc.m_ShaderFilePath = materialComponent["m_ShaderFilePath"].as<std::string>();
				mc.m_bUseColor = materialComponent["m_bUseColor"].as<bool>();
				mc.m_BaseColor = materialComponent["m_BaseColor"].as<glm::vec4>();
				mc.Load();
			}

			auto motorComponent = entity["MotorComponent"];
			if (motorComponent)
			{
				auto& mc = deserializeEntity.AddComponent<MotorComponent>();
				mc.m_RotationXAnglePerSecond = motorComponent["m_RotationXAnglePerSecond"].as<float>();
				mc.m_RotationYAnglePerSecond = motorComponent["m_RotationYAnglePerSecond"].as<float>();
			}

			SceneManager::GetInstance().m_Entities.insert({ deserializeEntity.GetEntityUid(), deserializeEntity });
			LOG_INFO("Deserialize Entity:" + deserializeEntity.GetComponent<TagComponent>().m_Tag + " complete");
		}
	}

	return true;
}

END_ENTERNITY

