#include "SceneManager.h"
#include "CameraController.h"
#include "Event/InputEventManager.h"

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

	m_CurrentCameraEntity = m_EditorCameraEntity;
	m_PlayerCameraController->Pause();

	//Entity cubeEntity(&m_Registry, "Cube Entity");
	//cubeEntity.AddComponent<TransformComponent>(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	//auto& cubeMeshComponent = cubeEntity.AddComponent<MeshComponent>();
	//auto& cubeMaterialComponent = cubeEntity.AddComponent<MaterialComponent>();
	//cubeMeshComponent.LoadMesh("assets/models/cube.mesh");
	//cubeMaterialComponent.LoadMaterial("assets/textures/skybox.jpeg", "assets/shaders/TestECS.glsl");
	//cubeMaterialComponent.SetMaterialProperty(0, glm::vec4(1.0f), 0);
	//cubeEntity.AddComponent<MotorComponent>();
	//
	//Entity planeEntity(&m_Registry, "Plane Entity");
	//planeEntity.AddComponent<TransformComponent>(glm::vec3(0.0f, -5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(100.0f, 1.0f, 100.0f));
	//auto& planeMeshComponent = planeEntity.AddComponent<MeshComponent>();
	//auto& planeMaterialComponent = planeEntity.AddComponent<MaterialComponent>();
	//planeMeshComponent.LoadMesh("assets/models/plane.mesh");
	//planeMaterialComponent.LoadMaterial("", "assets/shaders/TestECS.glsl");
	//planeMaterialComponent.SetMaterialProperty(1, glm::vec4(65.0f / 255, 90.0f / 255, 20.0f / 255, 1.0f), 0);


	//Entity lightEntity(&m_Registry, "Light Entity");
	//lightEntity.AddComponent<TransformComponent>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	//auto& lightMeshComponent = lightEntity.AddComponent<MeshComponent>();
	//auto& lightMaterialComponent = lightEntity.AddComponent<MaterialComponent>();
	//lightMeshComponent.LoadMesh("assets/models/sphere.mesh");
	//lightMaterialComponent.LoadMaterial("", "assets/shaders/TestECS.glsl");
	//lightMaterialComponent.SetMaterialProperty(1, glm::vec4(1.0f), 0);

	//m_Entities.insert({ cubeEntity.GetEntityUid(), cubeEntity });
	//m_Entities.insert({ planeEntity.GetEntityUid(), planeEntity });
	//m_Entities.insert({ lightEntity.GetEntityUid(), lightEntity });
	
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

void SceneManager::Update(float deltaTime)
{
	if (InputEventManager::GetInstance().IsKeyPress(Keyboard::GLFW_KEY_P))
	{
		m_CurrentCameraEntity = m_PlayerCameraEntity;
		m_EditorCameraController->Pause();
		m_PlayerCameraController->Start();
	}
	
	if (InputEventManager::GetInstance().IsKeyPress(Keyboard::GLFW_KEY_ESCAPE))
	{
		m_CurrentCameraEntity = m_EditorCameraEntity;
		m_EditorCameraController->Start();
		m_PlayerCameraController->Pause();
	}

	for (auto& entity : m_Entities)
	{
		if (entity.second.HasComponent<MotorComponent>())
		{
			auto& motorComponent = entity.second.GetComponent<MotorComponent>();
			if (entity.second.HasComponent<TransformComponent>())
			{
				auto& transformComponent = entity.second.GetComponent<TransformComponent>();
				transformComponent.RotateAlongYAxis(glm::radians(motorComponent.m_RotationYAnglePerSecond * deltaTime));
				transformComponent.RotateAlongXAxis(glm::radians(motorComponent.m_RotationXAnglePerSecond * deltaTime));
			}
		}
	}
}

void SceneManager::DrawSkyBox()
{
	glDepthFunc(GL_LEQUAL);
	auto& cameraTransformComponent = m_CurrentCameraEntity.GetComponent<TransformComponent>();
	auto& cameraCameraComponent = m_CurrentCameraEntity.GetComponent<CameraComponent>();


	auto& meshComponent = m_SkyBoxEntity.GetComponent<MeshComponent>();
	auto& skyboxComponet = m_SkyBoxEntity.GetComponent<SkyBoxComponent>();
	skyboxComponet.m_Shader->Bind();
	skyboxComponet.m_SkyBoxTexture->Bind();
	skyboxComponet.m_Shader->SetInteger1("skybox", 0);
	skyboxComponet.m_Shader->SetMat4f("u_mvp", cameraCameraComponent.m_ProjectMatrix * glm::mat4(glm::mat3(cameraTransformComponent.GetInverseWorldMatrix())));
	meshComponent.m_VertexArray->Bind();
	meshComponent.m_Indexbuffer->Bind();
	CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, meshComponent.m_Indexbuffer->GetCount(), GL_UNSIGNED_INT, (void*)0));
	glDepthFunc(GL_LESS);
}


void SceneManager::Tick(float deltaTime)
{
	Update(deltaTime);

	auto& cameraTransformComponent = m_CurrentCameraEntity.GetComponent<TransformComponent>();
	auto& cameraCameraComponent = m_CurrentCameraEntity.GetComponent<CameraComponent>();
	
	for (auto& entity : m_Entities)
	{
		auto& tagComponent = entity.second.GetComponent<TagComponent>();
		if (entity.second.HasComponent<TransformComponent>() && entity.second.HasComponent<MeshComponent>() && entity.second.HasComponent<MaterialComponent>())
		{
			auto& transformComponent = entity.second.GetComponent<TransformComponent>();
			auto& meshComponent = entity.second.GetComponent<MeshComponent>();
			auto& materialComponent = entity.second.GetComponent<MaterialComponent>();
			
			if(meshComponent.m_VertexArray)
				meshComponent.m_VertexArray->Bind();
			
			if (materialComponent.m_Shader)
			{
				materialComponent.m_Shader->Bind();
				materialComponent.m_Shader->SetMat4f("u_mvp", cameraCameraComponent.m_ProjectMatrix * cameraTransformComponent.GetInverseWorldMatrix() * transformComponent.GetWorldMatrix());
				materialComponent.m_Shader->SetInteger1("u_entityId", entity.second.GetEntityUid());
			}
		
			if (materialComponent.m_Texture)
				materialComponent.m_Texture->Bind(0);

			if (meshComponent.m_Indexbuffer)
			{
				meshComponent.m_Indexbuffer->Bind();
				CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, meshComponent.m_Indexbuffer->GetCount(), GL_UNSIGNED_INT, (void*)0));
			}
			//unbind
			if (meshComponent.m_VertexArray)
				meshComponent.m_VertexArray->UnBind();

			if (materialComponent.m_Shader)
			{
				materialComponent.m_Shader->UnBind();
			}
			if (materialComponent.m_Texture)
				materialComponent.m_Texture->UnBind();
			if (meshComponent.m_Indexbuffer)
			{
				meshComponent.m_Indexbuffer->UnBind();
			}
		}
	}

	DrawSkyBox();
}

void SceneManager::OnResize(int width, int height)
{
	m_CurrentCameraEntity.GetComponent<CameraComponent>().m_Aspect = static_cast<float>(width) / height;
	m_CurrentCameraEntity.GetComponent<CameraComponent>().ReCalculateProjectMatrix();

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

END_ENTERNITY


