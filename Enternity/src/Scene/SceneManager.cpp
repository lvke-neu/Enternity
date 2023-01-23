#include "SceneManager.h"
#include "CameraController.h"
#include "Event/InputEventManager.h"
#include "Renderer/RenderSystem.h"
#include "Physics/PhysicsSystem.h"

BEGIN_ENTERNITY

SceneManager::~SceneManager()
{
	auto viewMeshComponent = m_Registry.view<MeshComponent>();
	for (auto entity : viewMeshComponent)
	{
		auto& meshComponent = viewMeshComponent.get<MeshComponent>(entity);
		meshComponent.UnLoad();
	}
	auto viewMaterialComponent = m_Registry.view<MaterialComponent>();
	for (auto entity : viewMaterialComponent)
	{
		auto& materialComponent = viewMaterialComponent.get<MaterialComponent>(entity);
		materialComponent.UnLoad();
	}
	auto viewSkyBoxComponent = m_Registry.view<SkyBoxComponent>();
	for (auto entity : viewSkyBoxComponent)
	{
		auto& skyBoxComponent = viewSkyBoxComponent.get<SkyBoxComponent>(entity);
		skyBoxComponent.UnLoad();
	}

	Clear();
	m_EditorCameraEntity.Destroy();
	m_PlayerCameraEntity.Destroy();
	m_SkyBoxEntity.Destroy();
	SAFE_DELETE_SET_NULL(m_EditorCameraController);
	SAFE_DELETE_SET_NULL(m_PlayerCameraController);
}

void SceneManager::Initialize()
{	
	m_EditorCameraEntity = Entity(&m_Registry, "MainCamera Entity");
	m_EditorCameraEntity.AddComponent<TransformComponent>(glm::vec3(-5.684f, 2.305f, 3.188f), glm::vec3(-0.27f, -0.76f, 0.000f), glm::vec3(1.0f));
	m_EditorCameraEntity.AddComponent<CameraComponent>();
	m_EditorCameraController = new CameraController(m_EditorCameraEntity);
	
	m_PlayerCameraEntity = Entity(&m_Registry, "PlayerCamera Entity");
	m_PlayerCameraEntity.AddComponent<TransformComponent>(glm::vec3(-16.49f, -3.26, -12.25f), glm::vec3(glm::radians(15.65f) , glm::radians(-105.45f) , 0.000f), glm::vec3(1.0f));
	m_PlayerCameraEntity.AddComponent<CameraComponent>();
	m_PlayerCameraController = new CameraController(m_PlayerCameraEntity);
	m_PlayerCameraController->Pause();

	m_SkyBoxEntity = Entity(&m_Registry, "SkyBox Entity");
	auto& mc = m_SkyBoxEntity.AddComponent<MeshComponent>();
	mc.m_MeshFilePath = "assets/models/cube.mesh";
	mc.Load();
	auto& sc = m_SkyBoxEntity.AddComponent<SkyBoxComponent>();
	sc.m_ShaderFilePath = "assets/shaders/SkyBox.glsl";
	std::vector<std::string> textureFiles;
	textureFiles.push_back("assets/textures/skybox/default/right.jpg");
	textureFiles.push_back("assets/textures/skybox/default/left.jpg");
	textureFiles.push_back("assets/textures/skybox/default/top.jpg");
	textureFiles.push_back("assets/textures/skybox/default/bottom.jpg");
	textureFiles.push_back("assets/textures/skybox/default/front.jpg");
	textureFiles.push_back("assets/textures/skybox/default/back.jpg");
	sc.m_TexturePaths = textureFiles;
	sc.Load();
}



void SceneManager::Tick(float deltaTime)
{
	//physics
	PhysicsSystem::GetInstance().StepSimulation(deltaTime);
	for (auto& entity : m_Entities)
	{
		PhysicsSystem::GetInstance().UpdateEntityState(entity.second);
	}

	//render
	for (auto& entity : m_Entities)
	{
		RenderSystem::GetInstance().DrawEntity(m_SceneState == SceneState::Editor ? m_EditorCameraEntity : m_PlayerCameraEntity, entity.second);

		//render collider shape
		PhysicsSystem::GetInstance().ShowColliderShape(entity.second);
	}

	RenderSystem::GetInstance().DrawSkyBox(m_SceneState == SceneState::Editor ? m_EditorCameraEntity : m_PlayerCameraEntity, m_SkyBoxEntity);
}

void SceneManager::OnResize(int width, int height)
{
	m_EditorCameraEntity.GetComponent<CameraComponent>().m_Aspect = static_cast<float>(width) / height;
	m_EditorCameraEntity.GetComponent<CameraComponent>().ReCalculateProjectMatrix();

	m_PlayerCameraEntity.GetComponent<CameraComponent>().m_Aspect = static_cast<float>(width) / height;
	m_PlayerCameraEntity.GetComponent<CameraComponent>().ReCalculateProjectMatrix();
}

void SceneManager::Clear()
{
	for (auto& entity : m_Entities)
	{
		entity.second.Destroy();
	}
	m_Entities.clear();
}

void SceneManager::OnEditor()
{
	m_SceneState = SceneState::Editor;
	m_EditorCameraController->Start();
	m_PlayerCameraController->Pause();

	/*
		1.restore entity's transform property
		2.remove entity from physics world
	*/
	int index = 0;
	for (auto& entity : m_Entities)
	{
		if (entity.second.HasComponent<TransformComponent>())
		{
			auto& tc = entity.second.GetComponent<TransformComponent>();
			tc.m_Translation = m_EditorEntityTrans[index].m_Translation;
			tc.m_Scale = m_EditorEntityTrans[index].m_Scale;
			tc.m_Rotation = m_EditorEntityTrans[index].m_Rotation;
			index++;
		}

		PhysicsSystem::GetInstance().RemoveEntityFromPhysicsWorld(entity.second);
	}
}

void SceneManager::OnPlay()
{
	m_SceneState = SceneState::Player;
	m_EditorCameraController->Pause();
	m_PlayerCameraController->Start();

	/*
		1.save every entity's transform property
		2.add entity to physics world
	*/
	m_EditorEntityTrans.clear();
	int index = 0;
	for (auto& entity : m_Entities)
	{
		if (entity.second.HasComponent<TransformComponent>())
		{
			m_EditorEntityTrans.push_back(entity.second.GetComponent<TransformComponent>());
		}
		
		PhysicsSystem::GetInstance().AddEntityToPhysicsWorld(entity.second);
	}
}
END_ENTERNITY



