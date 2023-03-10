//#include "LightObject.h"
//#include "PerspectiveCamera/PerspectiveCamera.h"
//#include "Imgui/ImguiManager.h"
//
//BEGIN_ENTERNITY
//
//
//
//LightObject::LightObject()
//{
//	m_Transform.SetTranslation(glm::vec3(0.0f, 0.0f, 0.0f));
//
//	//vertexbuffer
//	struct VertexPosTex
//	{
//		glm::vec3 position;
//		glm::vec3 normal;
//		glm::vec2 texcoord;
//	};
//	
//	std::vector<VertexPosTex> vertices;
//	vertices.resize(24);
//	vertices[0].position = glm::vec3(1, -1, 1);
//	vertices[1].position = glm::vec3(1, 1, 1);
//	vertices[2].position = glm::vec3(1, 1, -1);
//	vertices[3].position = glm::vec3(1, -1, -1);
//
//	vertices[4].position = glm::vec3(-1, -1, -1);
//	vertices[5].position = glm::vec3(-1, 1, -1);
//	vertices[6].position = glm::vec3(-1, 1, 1);
//	vertices[7].position = glm::vec3(-1, -1, 1);
//
//	vertices[8].position =  glm::vec3(-1, 1, 1);
//	vertices[9].position =  glm::vec3(-1, 1, -1);
//	vertices[10].position = glm::vec3(1, 1, -1);
//	vertices[11].position = glm::vec3(1, 1, 1);
//
//	vertices[12].position = glm::vec3(1, -1, 1);
//	vertices[13].position = glm::vec3(1, -1, -1);
//	vertices[14].position = glm::vec3(-1, -1, -1);
//	vertices[15].position = glm::vec3(-1, -1, 1);
//
//	vertices[16].position = glm::vec3(1, -1, -1);
//	vertices[17].position = glm::vec3(1, 1, -1);
//	vertices[18].position = glm::vec3(-1, 1, -1);
//	vertices[19].position = glm::vec3(-1, -1, -1);
//
//	vertices[20].position = glm::vec3(-1, -1, 1);
//	vertices[21].position = glm::vec3(-1, 1, 1);
//	vertices[22].position = glm::vec3(1, 1, 1);
//	vertices[23].position = glm::vec3(1, -1, 1);
//
//	for (UINT i = 0; i < 4; ++i)
//	{
//		vertices[i].normal = glm::vec3(1.0f, 0.0f, 0.0f);
//
//		vertices[i + 4].normal = glm::vec3(-1.0f, 0.0f, 0.0f);
//
//		vertices[i + 8].normal = glm::vec3(0.0f, 1.0f, 0.0f);
//
//		vertices[i + 12].normal = glm::vec3(0.0f, -1.0f, 0.0f);
//
//		vertices[i + 16].normal = glm::vec3(0.0f, 0.0f, -1.0f);
//
//		vertices[i + 20].normal = glm::vec3(0.0f, 0.0f, 1.0f);
//	}
//
//	for (UINT i = 0; i < 6; ++i)
//	{
//		vertices[i * 4].texcoord =     glm::vec2(0.0f, 0.0f);
//		vertices[i * 4 + 1].texcoord = glm::vec2(0.0f, 1.0f);
//		vertices[i * 4 + 2].texcoord = glm::vec2(1.0f, 1.0f);
//		vertices[i * 4 + 3].texcoord = glm::vec2(1.0f, 0.0f);
//	}
//
//
//	vertexbuffer = new VertexBuffer(vertices.data(), (unsigned int)(sizeof(VertexPosTex) * vertices.size()));
//
//	//vertex array
//	vertexArray = new VertexArray;
//	VertexBufferLayout  vertexBufferLayout;
//	vertexBufferLayout.Push({ 0, 3, GL_FLOAT, false,  8 * sizeof(float), 0 });
//	vertexBufferLayout.Push({ 1, 3, GL_FLOAT, false,  8 * sizeof(float), 3 * sizeof(float) });
//	vertexBufferLayout.Push({ 2, 2, GL_FLOAT, false,  8 * sizeof(float), 6 * sizeof(float) });
//	vertexArray->Add(*vertexbuffer, vertexBufferLayout);
//
//	//index buffer
//	unsigned int indices[] =
//	{
//		0, 1, 2, 2, 3, 0,
//		4, 5, 6, 6, 7, 4,
//		8, 9, 10, 10, 11, 8,
//		12, 13, 14, 14, 15, 12,
//		16, 17, 18, 18, 19, 16,
//		20, 21, 22, 22, 23, 20
//	};
//	indexbuffer = new IndexBuffer(indices, 36);
//
//	//shader
//	shader = new Shader("assets/shaders/Light.glsl");
//	//shader->Bind();
//	//shader->SetFloat4("u_color1", 1.0f, 0.0f, 0.0f, 1.0f);
//	//shader->SetFloat4("u_color1", 1.0f, 0.0f, 0.0f, 1.0f);
//	//shader->SetFloat4("u_color13", 1.0f, 0.0f, 0.0f, 1.0f);
//	//shader->SetFloat4("u_color13", 1.0f, 0.0f, 0.0f, 1.0f);
//	
//	shader->Bind();
//
//	//unbind
//	vertexbuffer->UnBind();
//	indexbuffer->UnBind();
//	vertexArray->UnBind();
//	shader->UnBind();
//
//
//	//glEnable(GL_BLEND);
//	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	glEnable(GL_DEPTH_TEST);
//}
//
//void LightObject::draw()
//{
//	shader->Bind();
//	vertexArray->Bind();
//	indexbuffer->Bind();
//
//	operationScene();
//	CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, indexbuffer->GetCount(), GL_UNSIGNED_INT, (void*)0));
//}
//
//LightObject::~LightObject()
//{
//	SAFE_DELETE_SET_NULL(vertexbuffer);
//	SAFE_DELETE_SET_NULL(indexbuffer);
//	SAFE_DELETE_SET_NULL(vertexArray);
//	SAFE_DELETE_SET_NULL(shader);
//}
//
//void LightObject::operationScene()
//{
//	//model mat
//	glm::mat4 modelMat = m_Transform.GetWorldMatrix();
//
//	//view mat
//	glm::mat4 viewMat = PerspectiveCamera::GetInstance().GetViewMatrix();
//
//
//	//proj mat
//	glm::mat4 projMat = PerspectiveCamera::GetInstance().GetProjectMatrix();
//
//	shader->SetMat4f("u_mvp", projMat * viewMat * modelMat);
//}
//
//END_ENTERNITY