#include "Mesh.h"
#include "Common/Macro.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include <glad/glad.h>

namespace Enternity
{
	Mesh::~Mesh()
	{
		SAFE_DELETE_SET_NULL(m_vertexArray);
		SAFE_DELETE_SET_NULL(m_indexBuffer);
	}

	void Mesh::load(BlobHolder* blobHolder)
	{
		m_vertexArray = new VertexArray;
		m_indexBuffer = new IndexBuffer;
		m_vertexArray->load(blobHolder);
		m_indexBuffer->load(blobHolder);
		m_state = m_vertexArray->isLoadSucceeded() && m_indexBuffer->isLoadSucceeded() ? loading_state_succeeded : loading_state_failed;
	}

	void Mesh::unload()
	{
		if (m_vertexArray)
		{
			m_vertexArray->unload();
		}
		if (m_indexBuffer)
		{
			m_indexBuffer->unload();
		}
		SAFE_DELETE_SET_NULL(m_vertexArray);
		SAFE_DELETE_SET_NULL(m_indexBuffer);
		m_state = loading_state_pending;
	}

	void Mesh::bind()
	{
		if (m_vertexArray)
		{
			m_vertexArray->bind();
		}
		if (m_indexBuffer)
		{
			m_indexBuffer->bind();
		}
	}

	void Mesh::unbind()
	{
		if (m_vertexArray)
		{
			m_vertexArray->unbind();
		}
		if (m_indexBuffer)
		{
			m_indexBuffer->unbind();
		}
	}

	void Mesh::draw()
	{
		bind();
		if (m_indexBuffer)
		{
			glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, (void*)0);
		}
		unbind();
	}
}