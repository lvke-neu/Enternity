#include "Triangle.h"

#include "Imgui/ImguiManager.h"

BEGIN_ENTERNITY



Triangle::Triangle()
{
	//vertexbuffer
	struct VertexPosTex
	{
		glm::vec3 position;
		glm::vec2 texcoord;
	};

	std::vector<VertexPosTex> vertices;
	vertices.resize(24);
	vertices[0].position = glm::vec3(1, -1, -1);
	vertices[1].position = glm::vec3(1, 1, -1);
	vertices[2].position = glm::vec3(1, 1, 1);
	vertices[3].position = glm::vec3(1, -1, 1);

	vertices[4].position = glm::vec3(-1, -1, 1);
	vertices[5].position = glm::vec3(-1, 1, 1);
	vertices[6].position = glm::vec3(-1, 1, -1);
	vertices[7].position = glm::vec3(-1, -1, -1);

	vertices[8].position =  glm::vec3(-1, 1, -1);
	vertices[9].position =  glm::vec3(-1, 1, 1);
	vertices[10].position = glm::vec3(1, 1, 1);
	vertices[11].position = glm::vec3(1, 1, -1);

	vertices[12].position = glm::vec3(1, -1, -1);
	vertices[13].position = glm::vec3(1, -1, 1);
	vertices[14].position = glm::vec3(-1, -1, 1);
	vertices[15].position = glm::vec3(-1, -1, -1);

	vertices[16].position = glm::vec3(1, -1, 1);
	vertices[17].position = glm::vec3(1, 1, 1);
	vertices[18].position = glm::vec3(-1, 1, 1);
	vertices[19].position = glm::vec3(-1, -1, 1);

	vertices[20].position = glm::vec3(-1, -1, -1);
	vertices[21].position = glm::vec3(-1, 1, -1);
	vertices[22].position = glm::vec3(1, 1, -1);
	vertices[23].position = glm::vec3(1, -1, -1);

	for (UINT i = 0; i < 6; ++i)
	{
		vertices[i * 4].texcoord =     glm::vec2(0.0f, 1.0f);
		vertices[i * 4 + 1].texcoord = glm::vec2(0.0f, 0.0f);
		vertices[i * 4 + 2].texcoord = glm::vec2(1.0f, 0.0f);
		vertices[i * 4 + 3].texcoord = glm::vec2(1.0f, 1.0f);
	}


	vertexbuffer = new VertexBuffer(vertices.data(), (unsigned int)(sizeof(VertexPosTex) * vertices.size()));

	//vertex array
	vertexArray = new VertexArray;
	VertexBufferLayout  vertexBufferLayout;
	vertexBufferLayout.Push({ 0, 3, GL_FLOAT, false,  5 * sizeof(float), 0 });
	vertexBufferLayout.Push({ 1, 2, GL_FLOAT, false,  5 * sizeof(float), 3 * sizeof(float) });
	vertexArray->Add(*vertexbuffer, vertexBufferLayout);

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
	indexbuffer = new IndexBuffer(indices, 36);

	//shader
	shader = new Shader("shader/Basic.shader");
	//shader->Bind();
	//shader->SetFloat4("u_color1", 1.0f, 0.0f, 0.0f, 1.0f);
	//shader->SetFloat4("u_color1", 1.0f, 0.0f, 0.0f, 1.0f);
	//shader->SetFloat4("u_color13", 1.0f, 0.0f, 0.0f, 1.0f);
	//shader->SetFloat4("u_color13", 1.0f, 0.0f, 0.0f, 1.0f);
	
	//texture
	texture = new Texture("res/skybox.jpeg");
	texture->Bind(0);
	shader->Bind();
	shader->SetInteger1("u_texture", 0);


	
	//unbind
	vertexbuffer->UnBind();
	indexbuffer->UnBind();
	vertexArray->UnBind();
	shader->UnBind();
	texture->UnBind();

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Triangle::draw()
{
	shader->Bind();
	vertexArray->Bind();
	indexbuffer->Bind();
	texture->Bind(0);
	CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, indexbuffer->GetCount(), GL_UNSIGNED_INT, (void*)0));

	

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	static glm::vec3 camPos(0.0f, 0.0f, 10.0f);
	static glm::vec3 camRot(0.0f, 0.0f, 0.0f);

	static glm::vec3 modelPos(0.0f, 0.0f, 0.0f);
	static glm::vec3 modelRot(0.0f, 0.0f, 0.0f);
	static glm::vec3 modelScale(1.0f, 1.0f, 1.0f);

	static bool b = true;
	ImGui::ShowDemoWindow(&b);
	ImGui::ShowMetricsWindow(&b);

	ImGui::DragFloat3("CameraPos", &camPos[0], 0.1f, -9999.0f, 9999.0f);
	ImGui::DragFloat3("CameraRot", &camRot[0], 0.1f, -9999.0f, 9999.0f);

	ImGui::DragFloat3("ModelPos", &modelPos[0], 0.1f, -9999.0f, 9999.0f);
	ImGui::DragFloat3("ModelRot", &modelRot[0], 0.1f, -9999.0f, 9999.0f);
	ImGui::DragFloat3("ModelScale", &modelScale[0], 0.1f, -9999.0f, 9999.0f);




	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	operationScene(modelPos, modelRot, modelScale, camRot, camPos);
}

Triangle::~Triangle()
{
	SAFE_DELETE_SET_NULL(vertexbuffer);
	SAFE_DELETE_SET_NULL(indexbuffer);
	SAFE_DELETE_SET_NULL(vertexArray);
	SAFE_DELETE_SET_NULL(shader);
	SAFE_DELETE_SET_NULL(texture);
}

void Triangle::operationScene(glm::vec3 modelPos, glm::vec3 modelRot, glm::vec3 modelScale, glm::vec3 camRot, glm::vec3 camPos)
{
	//model mat
	glm::mat4 modelScaleMat = glm::scale(glm::mat4(1.0f), modelScale);
	glm::mat4 modelRotXMat = glm::rotate(glm::mat4(1.0f), modelRot.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 modelRotYMat = glm::rotate(glm::mat4(1.0f), modelRot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 modelRotZMat = glm::rotate(glm::mat4(1.0f), modelRot.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 modelPosMat = glm::translate(glm::mat4(1.0f), modelPos);
	glm::mat4 modelMat = modelPosMat  * modelRotXMat* modelRotYMat* modelRotZMat* modelScaleMat;

	//view mat
	glm::mat4 cameraScaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 cameraRotXMat = glm::rotate(glm::mat4(1.0f), camRot.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 cameraRotYMat = glm::rotate(glm::mat4(1.0f), camRot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 cameraRotZMat = glm::rotate(glm::mat4(1.0f), camRot.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 cameraPosMat = glm::translate(glm::mat4(1.0f), camPos);
	glm::mat4 viewMat = glm::inverse(cameraPosMat  * cameraRotXMat* cameraRotYMat* cameraRotZMat* cameraScaleMat);


	//proj mat
	glm::mat4 projMat = glm::perspective<float>(glm::pi<float>() / 3, 1200 / 600.0f, 1, 1000);

	shader->SetMat4f("u_mvp", projMat * viewMat * modelMat);
}

END_ENTERNITY