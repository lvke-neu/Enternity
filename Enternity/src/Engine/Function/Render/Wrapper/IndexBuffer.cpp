#include "IndexBuffer.h"
#include "Core/Log/Log.h"
#include "Core/Memory/Blob.h"
#include <glad/glad.h>

namespace Enternity
{
	void IndexBuffer::Destroy()
	{
		CHECK_GL_CALL(glDeleteBuffers(1, &m_renderId));
	}

	void IndexBuffer::init(Blob* blob)
	{
		ENTERNITY_ASSERT(blob != nullptr);

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