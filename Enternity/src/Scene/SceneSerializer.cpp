#include "SceneSerializer.h"
#include "File/FileOperation.h"

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
		out << YAML::Key << "m_Aspect" << YAML::Value << cameraComponent.m_Aspect;
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
	
	SerializeEntity(out, SceneManager::GetInstance().m_MainCameraEntity);

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

END_ENTERNITY

