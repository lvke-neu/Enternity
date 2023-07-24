#include "Mesh.h"
#include "Common/Macro.h"
#include "VertexArray.h"
#include <glad/glad.h>

namespace Enternity
{
	Mesh::~Mesh()
	{
		SAFE_DELETE_SET_NULL(m_vertexArray);
	}

	void Mesh::load(BlobHolder* blobHolder)
	{
		m_vertexArray = new VertexArray;
		m_vertexArray->load(blobHolder);
		m_state = m_vertexArray->isLoadSucceeded() ? loading_state_succeeded : loading_state_failed;
	}

	void Mesh::unload()
	{
		if (m_vertexArray)
		{
			m_vertexArray->unload();
		}
		SAFE_DELETE_SET_NULL(m_vertexArray);
		m_state = loading_state_pending;
	}

	void Mesh::bind()
	{
		if (m_vertexArray)
		{
			m_vertexArray->bind();
		}
	}

	void Mesh::unbind()
	{
		if (m_vertexArray)
		{
			m_vertexArray->unbind();
		}
	}

	void Mesh::draw()
	{
		bind();
		if (m_vertexArray)
		{
			glDrawElements(GL_TRIANGLES, m_vertexArray->getCount(), GL_UNSIGNED_INT, (void*)0);
		}
		unbind();
	}
}