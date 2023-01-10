#include "SceneManager.h"
#include "PerspectiveCamera/CameraController.h"
#include "TestDrawable/Triangle.h"
#include "ECS/Component/Component.h"
#include "PerspectiveCamera/PerspectiveCamera.h"
#include "Imgui/ImguiManager.h"

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



SceneManager::SceneManager()
{
	PerspectiveCamera::GetInstance().SetTranslation(glm::vec3(-11.769, 4.811, 1.297));
	PerspectiveCamera::GetInstance().SetRotation(glm::vec3(-0.330, -0.990, 0));

	m_CameraController = new CameraController();

	m_CubeEntity = Entity(&m_Registry, "Cube");
	m_CubeEntity.AddComponent<TransformComponent>();
	m_CubeEntity.AddComponent<MeshComponent>();


	InitializeComponent();

	ImguiDrawEventManager::GetInstance().RegisterEvent(this);
}

SceneManager::~SceneManager()
{
	SAFE_DELETE_SET_NULL(m_CameraController);
	ImguiDrawEventManager::GetInstance().UnRegisterEvent(this);
}

void SceneManager::Tick(float deltaTime)
{

	auto& transformComponent = m_CubeEntity.GetComponent<TransformComponent>();
	auto& meshComponent = m_CubeEntity.GetComponent<MeshComponent>();
	meshComponent.m_Shader->Bind();
	//model mat
	glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), transformComponent.m_Translation) * glm::mat4_cast(glm::qua<float>(transformComponent.m_Rotation)) *glm::scale(glm::mat4(1.0f), transformComponent.m_Scale);

	//view mat
	glm::mat4 viewMat = PerspectiveCamera::GetInstance().GetViewMatrix();


	//proj mat
	glm::mat4 projMat = PerspectiveCamera::GetInstance().GetProjectMatrix();
	meshComponent.m_Shader->SetMat4f("u_mvp", projMat * viewMat * modelMat);
	meshComponent.m_VertexArray->Bind();
	meshComponent.m_Indexbuffer->Bind();
	meshComponent.m_Texture->Bind(0);

	CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, meshComponent.m_Indexbuffer->GetCount(), GL_UNSIGNED_INT, (void*)0));

}

void SceneManager::ImguiDraw()
{
	auto& transformComponent = m_CubeEntity.GetComponent<TransformComponent>();

	ImGui::Begin("Cube Property");

	ImGui::DragFloat3("CubePos", &transformComponent.m_Translation[0], 0.1f, -9999.0f, 9999.0f);
	ImGui::DragFloat3("CubeRot", &transformComponent.m_Rotation[0], 0.1f, -9999.0f, 9999.0f);
	ImGui::DragFloat3("CubeScale", &transformComponent.m_Scale[0], 0.1f, -9999.0f, 9999.0f);

	ImGui::End();


}



END_ENTERNITY


