#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Core/Log/Log.h"
#include "Core/Blob/Blob.h"
#include "Utility/Utility.h"
#include <glad/glad.h>

namespace Enternity
{
	VertexArray::~VertexArray()
	{
		CHECK_GL_CALL(glDeleteVertexArrays(1, &m_renderId));
	}

	void VertexArray::init(VertexBuffer* vertexBuffer)
	{
		CHECK_GL_CALL(glGenVertexArrays(1, &m_renderId));
		CHECK_GL_CALL(glBindVertexArray(m_renderId));
		vertexBuffer->bind();
		const auto& elements = vertexBuffer->getVertexBufferLayout().getElements();
		for (const auto& element : elements)
		{
			CHECK_GL_CALL(glEnableVertexAttribArray(element.index));
			CHECK_GL_CALL(glVertexAttribPointer(element.index, element.count, element.type, element.normalized, element.stride, (void*)(element.start)));
		}
		vertexBuffer->unbind();
		CHECK_GL_CALL(glBindVertexArray(0));
	}

	void VertexArray::bind()
	{
		CHECK_GL_CALL(glBindVertexArray(m_renderId));
	}

	void VertexArray::unbind()
	{
		CHECK_GL_CALL(glBindVertexArray(0));
	}
}