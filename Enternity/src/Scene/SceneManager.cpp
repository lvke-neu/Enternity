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
	SAFE_DELETE_SET_NULL(m_SceneHierarchyPanel)
}

void SceneManager::Initialize()
{
	m_MainCameraEntity = Entity(&m_Registry, "MainCamera Entity");
	m_MainCameraEntity.AddComponent<TransformComponent>(glm::vec3(-2.944f, 2.843f, -1.980), glm::vec3(-0.570f, -0.740f, 0.000f), glm::vec3(1.0f));
	m_MainCameraEntity.AddComponent<CameraComponent>();
	m_CameraController = new CameraController(&m_MainCameraEntity);


	m_CubeEntity = Entity(&m_Registry, "Cube Entity");
	m_CubeEntity.AddComponent<TransformComponent>(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	auto& cubeMeshComponent = m_CubeEntity.AddComponent<MeshComponent>();
	auto& cubeMaterialComponent = m_CubeEntity.AddComponent<MaterialComponent>();
	cubeMeshComponent.LoadMesh("assets/model/cube_mesh.bin");
	cubeMaterialComponent.LoadMaterial("assets/textures/skybox.jpeg", "assets/shaders/TestECS.glsl");


	
	m_PlaneEntity = Entity(&m_Registry, "plane Entity");
	m_PlaneEntity.AddComponent<TransformComponent>(glm::vec3(0.0f, -5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(100.0f, 1.0f, 100.0f));
	auto& planeMeshComponent = m_PlaneEntity.AddComponent<MeshComponent>();
	auto& planeMaterialComponent = m_PlaneEntity.AddComponent<MaterialComponent>();
	planeMeshComponent.LoadMesh("assets/model/plane_mesh.bin");
	planeMaterialComponent.LoadMaterial("", "assets/shaders/TestECS.glsl");
	

	m_SceneHierarchyPanel = new SceneHierarchyPanel(&m_Registry);
}

void SceneManager::Tick(float deltaTime)
{
	auto& cameraTransformComponent = m_MainCameraEntity.GetComponent<TransformComponent>();
	auto& cameraCameraComponent = m_MainCameraEntity.GetComponent<CameraComponent>();

	auto& cubeTransformComponent = m_CubeEntity.GetComponent<TransformComponent>();
	auto& cubeMeshComponent = m_CubeEntity.GetComponent<MeshComponent>();
	auto& cubeMaterialComponent = m_CubeEntity.GetComponent<MaterialComponent>();
	cubeMaterialComponent.m_Shader->Bind();
	cubeMaterialComponent.m_Shader->SetMat4f("u_mvp", cameraCameraComponent.m_ProjectMatrix * cameraTransformComponent.GetInverseWorldMatrix() * cubeTransformComponent.GetWorldMatrix());
	cubeMaterialComponent.m_Texture->Bind(0);
	cubeMeshComponent.m_VertexArray->Bind();
	cubeMeshComponent.m_Indexbuffer->Bind();
	cubeMaterialComponent.m_Shader->SetInteger1("u_texture", 0);
	cubeMaterialComponent.m_Shader->SetInteger1("b_useColor", 0);
	
	CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, cubeMeshComponent.m_Indexbuffer->GetCount(), GL_UNSIGNED_INT, (void*)0));


	auto& planeTransformComponent = m_PlaneEntity.GetComponent<TransformComponent>();
	auto& planMeshComponent = m_PlaneEntity.GetComponent<MeshComponent>();
	auto& planMaterialComponent = m_PlaneEntity.GetComponent<MaterialComponent>();
	planMaterialComponent.m_Shader->Bind();
	planMaterialComponent.m_Shader->SetMat4f("u_mvp", cameraCameraComponent.m_ProjectMatrix * cameraTransformComponent.GetInverseWorldMatrix() * planeTransformComponent.GetWorldMatrix());
	planMeshComponent.m_VertexArray->Bind();
	planMeshComponent.m_Indexbuffer->Bind();
	planMaterialComponent.m_Shader->SetInteger1("b_useColor", 1);
	planMaterialComponent.m_Shader->SetFloat4("u_baseColor", glm::vec4(65.0f / 255, 90.0f / 255, 20.0f / 255, 1.0f));
	CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, planMeshComponent.m_Indexbuffer->GetCount(), GL_UNSIGNED_INT, (void*)0));

}

void SceneManager::OnResize(int width, int height)
{
	m_MainCameraEntity.GetComponent<CameraComponent>().m_ProjectMatrix =
		glm::perspective<float>(glm::pi<float>() / 3, static_cast<float>(width) / height, 1, 1000);
}

END_ENTERNITY


