#include "VertexArray.h"

BEGIN_ENTERNITY

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_rendererId);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_rendererId);
}

void VertexArray::Add(const VertexBuffer & vertexBuffer, const VertexBufferLayout & vertexBufferLayout)
{
	Bind();
	vertexBuffer.Bind();
	const auto& elements = vertexBufferLayout.GetElements();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		glEnableVertexAttribArray(elements[i].index);
		glVertexAttribPointer(elements[i].index, elements[i].count, elements[i].type, elements[i].normalized, elements[i].stride, (void*)0);
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_rendererId);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

END_ENTERNITY

