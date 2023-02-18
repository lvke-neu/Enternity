#include "VertexBuffer.h"
#include "Core/Log/Log.h"
#include "Core/Memory/Blob.h"
#include <glad/glad.h>

namespace Enternity
{
	void VertexBuffer::Destroy()
	{
		CHECK_GL_CALL(glDeleteBuffers(1, &m_renderId));
	}

	void VertexBuffer::init(Blob* blob, const VertexBufferLayout& vertexBufferLayout)
	{
		ENTERNITY_ASSERT(blob != nullptr);

		Destroy();
		
		glGenBuffers(1, &m_renderId);
		CHECK_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_renderId));
		CHECK_GL_CALL(glBufferData(GL_ARRAY_BUFFER, blob->getLength(), blob->getData(), GL_STATIC_DRAW));
		CHECK_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));

		m_vertexBufferLayout = vertexBufferLayout;
	}

	void VertexBuffer::bind()
	{
		CHECK_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_renderId));
	}

	void VertexBuffer::unbind()
	{
		CHECK_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	VertexBufferLayout VertexBuffer::getVertexBufferLayout() const
	{
		return m_vertexBufferLayout;
	}

}
