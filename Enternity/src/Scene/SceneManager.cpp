#include "SceneManager.h"
#include "CameraController.h"
#include "SceneHierarchyPanel.h"

BEGIN_ENTERNITY

void SceneManager::InitializeComponent()
{
	if (m_CubeEntity.HasComponent<TransformComponent>())
	{
		auto& transformComponent = m_CubeEntity.GetComponent<TransformComponent>();
	}
	
	if (m_CubeEntity.HasComponent<MeshComponent>())
	{
		auto& meshComponent = m_CubeEntity.GetComponent<MeshComponent>();

		//vertexbuffer
		struct VertexPosTex
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 texcoord;
		};

		std::vector<VertexPosTex> vertices;
		vertices.resize(24);
		vertices[0].position = glm::vec3(1, -1, 1);
		vertices[1].position = glm::vec3(1, 1, 1);
		vertices[2].position = glm::vec3(1, 1, -1);
		vertices[3].position = glm::vec3(1, -1, -1);

		vertices[4].position = glm::vec3(-1, -1, -1);
		vertices[5].position = glm::vec3(-1, 1, -1);
		vertices[6].position = glm::vec3(-1, 1, 1);
		vertices[7].position = glm::vec3(-1, -1, 1);

		vertices[8].position = glm::vec3(-1, 1, 1);
		vertices[9].position = glm::vec3(-1, 1, -1);
		vertices[10].position = glm::vec3(1, 1, -1);
		vertices[11].position = glm::vec3(1, 1, 1);

		vertices[12].position = glm::vec3(1, -1, 1);
		vertices[13].position = glm::vec3(1, -1, -1);
		vertices[14].position = glm::vec3(-1, -1, -1);
		vertices[15].position = glm::vec3(-1, -1, 1);

		vertices[16].position = glm::vec3(1, -1, -1);
		vertices[17].position = glm::vec3(1, 1, -1);
		vertices[18].position = glm::vec3(-1, 1, -1);
		vertices[19].position = glm::vec3(-1, -1, -1);

		vertices[20].position = glm::vec3(-1, -1, 1);
		vertices[21].position = glm::vec3(-1, 1, 1);
		vertices[22].position = glm::vec3(1, 1, 1);
		vertices[23].position = glm::vec3(1, -1, 1);

		for (UINT i = 0; i < 4; ++i)
		{
			vertices[i].normal = glm::vec3(1.0f, 0.0f, 0.0f);

			vertices[i + 4].normal = glm::vec3(-1.0f, 0.0f, 0.0f);

			vertices[i + 8].normal = glm::vec3(0.0f, 1.0f, 0.0f);

			vertices[i + 12].normal = glm::vec3(0.0f, -1.0f, 0.0f);

			vertices[i + 16].normal = glm::vec3(0.0f, 0.0f, -1.0f);

			vertices[i + 20].normal = glm::vec3(0.0f, 0.0f, 1.0f);
		}

		for (UINT i = 0; i < 6; ++i)
		{
			vertices[i * 4].texcoord = glm::vec2(0.0f, 0.0f);
			vertices[i * 4 + 1].texcoord = glm::vec2(0.0f, 1.0f);
			vertices[i * 4 + 2].texcoord = glm::vec2(1.0f, 1.0f);
			vertices[i * 4 + 3].texcoord = glm::vec2(1.0f, 0.0f);
		}


		meshComponent.m_Vertexbuffer = new VertexBuffer(vertices.data(), (unsigned int)(sizeof(VertexPosTex) * vertices.size()));
		
		//vertex array
		meshComponent.m_VertexArray = new VertexArray;
		VertexBufferLayout  vertexBufferLayout;
		vertexBufferLayout.Push({ 0, 3, GL_FLOAT, false,  8 * sizeof(float), 0 });
		vertexBufferLayout.Push({ 1, 3, GL_FLOAT, false,  8 * sizeof(float), 3 * sizeof(float) });
		vertexBufferLayout.Push({ 2, 2, GL_FLOAT, false,  8 * sizeof(float), 6 * sizeof(float) });
		meshComponent.m_VertexArray->Add(*meshComponent.m_Vertexbuffer, vertexBufferLayout);

		//index buffer
		unsigned int indices[] =
		{
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4,
			8, 9, 10, 10, 11, 8,
			12, 13, 14, 14, 15, 12,
			16, 17, 18, 18, 19, 16,
			20, 21, 22, 22, 23, 20
		};
		meshComponent.m_Indexbuffer = new IndexBuffer(indices, 36);

		//shader
		meshComponent.m_Shader = new Shader("assets/shaders/TestECS.glsl");
		meshComponent.m_Shader->Bind();
		//texture
		meshComponent.m_Texture = new Texture("assets/textures/skybox.jpeg");
		meshComponent.m_Shader->SetInteger1("u_texture", 0);
	}
	
}


SceneManager::~SceneManager()
{
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
	auto& cubeMeshComponent = m_CubeEntity.AddComponent<MeshComponent>("assets/model/cube_mesh.bin", "assets/textures/skybox.jpeg", "assets/shaders/TestECS.glsl");
	cubeMeshComponent.m_Shader->Bind();
	cubeMeshComponent.m_Shader->SetInteger1("u_texture", 0);
	//InitializeComponent();

	m_PlaneEntity = Entity(&m_Registry, "Plane Entity");
	m_PlaneEntity.AddComponent<TransformComponent>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	auto& planeMeshComponent = m_PlaneEntity.AddComponent<MeshComponent>("assets/model/cube_mesh.bin", "assets/textures/skybox.jpeg", "assets/shaders/TestECS.glsl");
	planeMeshComponent.m_Shader->Bind();
	planeMeshComponent.m_Shader->SetInteger1("u_texture", 0);

	m_SceneHierarchyPanel = new SceneHierarchyPanel(&m_Registry);
}

void SceneManager::Tick(float deltaTime)
{
	auto& cameraTransformComponent = m_MainCameraEntity.GetComponent<TransformComponent>();
	auto& cameraCameraComponent = m_MainCameraEntity.GetComponent<CameraComponent>();

	auto& cubeTransformComponent = m_CubeEntity.GetComponent<TransformComponent>();
	auto& cubeMeshComponent = m_CubeEntity.GetComponent<MeshComponent>();
	cubeMeshComponent.m_Shader->Bind();
	cubeMeshComponent.m_Shader->SetMat4f("u_mvp", cameraCameraComponent.m_ProjectMatrix * cameraTransformComponent.GetInverseWorldMatrix() * cubeTransformComponent.GetWorldMatrix());
	cubeMeshComponent.m_VertexArray->Bind();
	cubeMeshComponent.m_Indexbuffer->Bind();
	cubeMeshComponent.m_Texture->Bind(0);
	CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, cubeMeshComponent.m_Indexbuffer->GetCount(), GL_UNSIGNED_INT, (void*)0));

	auto& planeTransformComponent = m_PlaneEntity.GetComponent<TransformComponent>();
	auto& planeMeshComponent = m_PlaneEntity.GetComponent<MeshComponent>();
	planeMeshComponent.m_Shader->Bind();
	planeMeshComponent.m_Shader->SetMat4f("u_mvp", cameraCameraComponent.m_ProjectMatrix * cameraTransformComponent.GetInverseWorldMatrix() * planeTransformComponent.GetWorldMatrix());
	planeMeshComponent.m_VertexArray->Bind();
	planeMeshComponent.m_Indexbuffer->Bind();
	planeMeshComponent.m_Texture->Bind(0);
	CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, planeMeshComponent.m_Indexbuffer->GetCount(), GL_UNSIGNED_INT, (void*)0));

}

void SceneManager::OnResize(int width, int height)
{
	m_MainCameraEntity.GetComponent<CameraComponent>().m_ProjectMatrix =
		glm::perspective<float>(glm::pi<float>() / 3, static_cast<float>(width) / height, 1, 1000);
}

END_ENTERNITY


