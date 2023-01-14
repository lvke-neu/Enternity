#include "SceneManager.h"
#include "CameraController.h"
#include "SceneHierarchyPanel.h"


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

	SAFE_DELETE_SET_NULL(m_CameraController);
	SAFE_DELETE_SET_NULL(m_SceneHierarchyPanel);
}

void SceneManager::Initialize()
{

	m_MainCameraEntity = Entity(&m_Registry, "MainCamera Entity");
	m_MainCameraEntity.AddComponent<TransformComponent>(glm::vec3(-5.684f, 2.305f, 3.188f), glm::vec3(-0.27f, -0.76f, 0.000f), glm::vec3(1.0f));
	m_MainCameraEntity.AddComponent<CameraComponent>();
	m_CameraController = new CameraController(m_MainCameraEntity);


	Entity cubeEntity(&m_Registry, "Cube Entity");
	cubeEntity.AddComponent<TransformComponent>(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	auto& cubeMeshComponent = cubeEntity.AddComponent<MeshComponent>();
	auto& cubeMaterialComponent = cubeEntity.AddComponent<MaterialComponent>();
	cubeMeshComponent.LoadMesh("assets/model/cube_mesh.bin");
	cubeMaterialComponent.LoadMaterial("assets/textures/skybox.jpeg", "assets/shaders/TestECS.glsl");
	cubeMaterialComponent.SetMaterialProperty(0, glm::vec4(1.0f), 0);

	
	Entity planeEntity(&m_Registry, "Plane Entity");
	planeEntity.AddComponent<TransformComponent>(glm::vec3(0.0f, -5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(100.0f, 1.0f, 100.0f));
	auto& planeMeshComponent = planeEntity.AddComponent<MeshComponent>();
	auto& planeMaterialComponent = planeEntity.AddComponent<MaterialComponent>();
	planeMeshComponent.LoadMesh("assets/model/plane_mesh.bin");
	planeMaterialComponent.LoadMaterial("", "assets/shaders/TestECS.glsl");
	planeMaterialComponent.SetMaterialProperty(1, glm::vec4(65.0f / 255, 90.0f / 255, 20.0f / 255, 1.0f), 0);


	Entity lightEntity(&m_Registry, "Light Entity");
	lightEntity.AddComponent<TransformComponent>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	auto& lightMeshComponent = lightEntity.AddComponent<MeshComponent>();
	auto& lightMaterialComponent = lightEntity.AddComponent<MaterialComponent>();
	lightMeshComponent.LoadMesh("assets/model/sphere_mesh.bin");
	lightMaterialComponent.LoadMaterial("", "assets/shaders/TestECS.glsl");
	lightMaterialComponent.SetMaterialProperty(1, glm::vec4(1.0f), 0);

	m_Entities.insert({ cubeEntity.GetEntityUid(), cubeEntity });
	m_Entities.insert({ planeEntity.GetEntityUid(), planeEntity });
	m_Entities.insert({ lightEntity.GetEntityUid(), lightEntity });
	

	m_SceneHierarchyPanel = new SceneHierarchyPanel;
}

void SceneManager::Tick(float deltaTime)
{
	auto& cameraTransformComponent = m_MainCameraEntity.GetComponent<TransformComponent>();
	auto& cameraCameraComponent = m_MainCameraEntity.GetComponent<CameraComponent>();
	
	for (auto& entity : m_Entities)
	{
		if (entity.second.HasComponent<TransformComponent>() && entity.second.HasComponent<MeshComponent>() && entity.second.HasComponent<MaterialComponent>())
		{
			auto& transformComponent = entity.second.GetComponent<TransformComponent>();
			auto& meshComponent = entity.second.GetComponent<MeshComponent>();
			auto& materialComponent = entity.second.GetComponent<MaterialComponent>();

			meshComponent.m_VertexArray->Bind();
			meshComponent.m_Indexbuffer->Bind();
			materialComponent.m_Shader->Bind();
			materialComponent.m_Shader->SetMat4f("u_mvp", cameraCameraComponent.m_ProjectMatrix * cameraTransformComponent.GetInverseWorldMatrix() * transformComponent.GetWorldMatrix());
			materialComponent.m_Texture->Bind(0);
			CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, meshComponent.m_Indexbuffer->GetCount(), GL_UNSIGNED_INT, (void*)0));
		}
	}
}

void SceneManager::OnResize(int width, int height)
{
	m_MainCameraEntity.GetComponent<CameraComponent>().aspect = static_cast<float>(width) / height;
	m_MainCameraEntity.GetComponent<CameraComponent>().ReCalculateProjectMatrix();
}

END_ENTERNITY


