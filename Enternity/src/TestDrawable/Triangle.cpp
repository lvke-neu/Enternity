#include "Triangle.h"


BEGIN_ENTERNITY

Triangle::Triangle()
{
	//vertexbuffer
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f, 1.0f,0.0f,0.0f,
		 0.5f, -0.5,  0.0f, 0.0f,1.0f,0.0f,
		 0.5f, 0.5,  0.0f,  0.0f,0.0f,1.0f,
		 -0.5f, 0.5f, 0.0f, 0.0f,0.0f,1.0f
	};
	vertexbuffer = new VertexBuffer(vertices, sizeof(vertices));

	//vertex array
	vertexArray = new VertexArray;
	VertexBufferLayout  vertexBufferLayout;
	vertexBufferLayout.Push({ 0, 3, GL_FLOAT, false,  6 * sizeof(float), 0 });
	vertexBufferLayout.Push({ 1, 3, GL_FLOAT, false,  6 * sizeof(float), 3 * sizeof(float) });
	vertexArray->Add(*vertexbuffer, vertexBufferLayout);

	//index buffer
	unsigned int indices[] =
	{ 0,1,2,2,3,0 };
	indexbuffer = new IndexBuffer(indices, 6);

	//shader
	shader = new Shader("shader/Basic.shader");
	shader->Bind();
	shader->setFloat4("u_color1", 1.0f, 0.0f, 0.0f, 1.0f);
	shader->setFloat4("u_color2", 0.0f, 1.0f, 0.0f, 1.0f);
	
	

	//unbind
	vertexbuffer->UnBind();
	indexbuffer->UnBind();
	vertexArray->UnBind();
	shader->UnBind();
}

void Triangle::draw()
{
	shader->Bind();
	vertexArray->Bind();
	indexbuffer->Bind();
	CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, indexbuffer->GetCount(), GL_UNSIGNED_INT, (void*)0));
}

Triangle::~Triangle()
{
	SAFE_DELETE_SET_NULL(vertexbuffer);
	SAFE_DELETE_SET_NULL(indexbuffer);
	SAFE_DELETE_SET_NULL(vertexArray);
}

END_ENTERNITY