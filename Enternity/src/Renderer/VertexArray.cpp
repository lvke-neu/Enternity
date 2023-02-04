#include "VertexArray.h"

BEGIN_ENTERNITY

VertexArray::VertexArray()
{
	CHECK_GL_CALL(glGenVertexArrays(1, &m_rendererId));
}

VertexArray::~VertexArray()
{
	CHECK_GL_CALL(glDeleteVertexArrays(1, &m_rendererId));
}

void VertexArray::Add(const VertexBuffer & vertexBuffer, const VertexBufferLayout & vertexBufferLayout)
{
	Bind();
	vertexBuffer.Bind();
	const auto& elements = vertexBufferLayout.GetElements();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		CHECK_GL_CALL(glEnableVertexAttribArray(elements[i].index));
		if (elements[i].type == GL_INT)
		{
			CHECK_GL_CALL(glVertexAttribIPointer(elements[i].index, elements[i].count, elements[i].type, elements[i].stride, (void*)(elements[i].start)));
		}
		else if (elements[i].type == GL_FLOAT)
		{
			CHECK_GL_CALL(glVertexAttribPointer(elements[i].index, elements[i].count, elements[i].type, elements[i].normalized, elements[i].stride, (void*)(elements[i].start)));
		}		
	}
}

void VertexArray::Bind(unsigned int slot) const
{
	CHECK_GL_CALL(glBindVertexArray(m_rendererId));
}

void VertexArray::UnBind() const
{
	CHECK_GL_CALL(glBindVertexArray(0));
}

END_ENTERNITY

