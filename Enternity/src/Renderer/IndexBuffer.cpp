#include "IndexBuffer.h"

BEGIN_ENTERNITY

IndexBuffer::IndexBuffer(const unsigned int * indices, unsigned int count):
	m_count(count)
{
	glGenBuffers(1, &m_rendererId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	CHECK_GL_CALL(glDeleteBuffers(1, &m_rendererId));
}

void IndexBuffer::Bind() const
{
	CHECK_GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId));
}

void IndexBuffer::UnBind() const
{
	CHECK_GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

END_ENTERNITY