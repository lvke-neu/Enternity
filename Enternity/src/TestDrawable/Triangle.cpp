#include "Triangle.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

BEGIN_ENTERNITY

Triangle::Triangle()
{
	//vertexbuffer
	float vertices[] =
	{
		-0.5f, -0.5f, -5.0f,		1.0f,0.0f,0.0f,		0.0f,0.0f,
		 0.5f, -0.5,  -5.0f,		0.0f,1.0f,0.0f,		1.0f,0.0f,
		 0.5f, 0.5,  -5.0f,		0.0f,0.0f,1.0f,		1.0f,1.0f,
		 -0.5f, 0.5f, -5.0f,		0.0f,0.0f,1.0f,		0.0f,1.0f
	};
	vertexbuffer = new VertexBuffer(vertices, sizeof(vertices));

	//vertex array
	vertexArray = new VertexArray;
	VertexBufferLayout  vertexBufferLayout;
	vertexBufferLayout.Push({ 0, 3, GL_FLOAT, false,  8 * sizeof(float), 0 });
	vertexBufferLayout.Push({ 1, 3, GL_FLOAT, false,  8 * sizeof(float), 3 * sizeof(float) });
	vertexBufferLayout.Push({ 2, 2, GL_FLOAT, false,  8 * sizeof(float), 6 * sizeof(float) });
	vertexArray->Add(*vertexbuffer, vertexBufferLayout);

	//index buffer
	unsigned int indices[] =
	{ 0,1,2,2,3,0 };
	indexbuffer = new IndexBuffer(indices, 6);

	//shader
	shader = new Shader("shader/Basic.shader");
	//shader->Bind();
	//shader->SetFloat4("u_color1", 1.0f, 0.0f, 0.0f, 1.0f);
	//shader->SetFloat4("u_color1", 1.0f, 0.0f, 0.0f, 1.0f);
	//shader->SetFloat4("u_color13", 1.0f, 0.0f, 0.0f, 1.0f);
	//shader->SetFloat4("u_color13", 1.0f, 0.0f, 0.0f, 1.0f);
	
	//texture
	texture = new Texture("res/atmosphere.png");
	texture->Bind(0);
	shader->Bind();
	shader->SetInteger1("u_texture", 0);

	glm::mat4 projMat = glm::perspective<float>(glm::pi<float>() / 3, 800 / 600.0f, 1, 1000);
	shader->SetMat4f("u_mvp", projMat);
	
	//unbind
	vertexbuffer->UnBind();
	indexbuffer->UnBind();
	vertexArray->UnBind();
	shader->UnBind();
	texture->UnBind();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Triangle::draw()
{
	shader->Bind();
	vertexArray->Bind();
	indexbuffer->Bind();
	texture->Bind(0);
	CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, indexbuffer->GetCount(), GL_UNSIGNED_INT, (void*)0));
}

Triangle::~Triangle()
{
	SAFE_DELETE_SET_NULL(vertexbuffer);
	SAFE_DELETE_SET_NULL(indexbuffer);
	SAFE_DELETE_SET_NULL(vertexArray);
	SAFE_DELETE_SET_NULL(shader);
	SAFE_DELETE_SET_NULL(texture);
}

END_ENTERNITY