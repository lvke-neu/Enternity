#include "VertexBuffer.h"

BEGIN_ENTERNITY

VertexBuffer::VertexBuffer(const void* vertices, unsigned int size)
{
	CHECK_GL_CALL(glGenBuffers(1, &m_rendererId));
	CHECK_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererId));
	CHECK_GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	CHECK_GL_CALL(glDeleteBuffers(1, &m_rendererId));
}

void VertexBuffer::Bind() const
{
	CHECK_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererId));
}

void VertexBuffer::UnBind() const
{
	CHECK_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

END_ENTERNITY