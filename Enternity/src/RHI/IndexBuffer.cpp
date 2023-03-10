#include "IndexBuffer.h"
#include "Core/Log/Log.h"
#include "Core/Blob/Blob.h"
#include "Utility/Utility.h"
#include <glad/glad.h>

namespace Enternity
{
	IndexBuffer::~IndexBuffer()
	{
		CHECK_GL_CALL(glDeleteBuffers(1, &m_renderId));
	}

	void IndexBuffer::init(Blob* blob)
	{
		m_count = (unsigned int)blob->getLength() / sizeof(unsigned int);

		CHECK_GL_CALL(glGenBuffers(1, &m_renderId));
		CHECK_GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderId));
		CHECK_GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, blob->getLength(), blob->getData(), GL_STATIC_DRAW));
		CHECK_GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	void IndexBuffer::bind()
	{
		CHECK_GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderId));
	}

	void IndexBuffer::unbind()
	{
		CHECK_GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}