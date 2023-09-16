#include "UniformBuffer.h"
#include <glad/glad.h>

namespace Enternity
{
	UniformBuffer::UniformBuffer()
	{
		glGenBuffers(1, &m_renderId);
	}

	UniformBuffer::~UniformBuffer()
	{
		glDeleteBuffers(1, &m_renderId);
	}

	void UniformBuffer::modify(const void* data, unsigned int size, unsigned int bindPoint)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_renderId);
		glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW);
		glBindBufferRange(GL_UNIFORM_BUFFER, bindPoint, m_renderId, 0, size);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}