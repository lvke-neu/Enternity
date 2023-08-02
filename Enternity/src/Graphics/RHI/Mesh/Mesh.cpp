#include "Mesh.h"
#include "MeshBlobHolder.h"
#include "Engine/Blob.h"
#include <glad/glad.h>

namespace Enternity
{
	Mesh::~Mesh()
	{
		glDeleteBuffers(1, &m_vbId);
		glDeleteBuffers(1, &m_ibId);
		glDeleteVertexArrays(1, &m_renderId);
	}

	void Mesh::load(BlobHolder* blobHolder)
	{
		MeshBlobHolder* meshBlobHolder = dynamic_cast<MeshBlobHolder*>(blobHolder);
		if (!meshBlobHolder || !meshBlobHolder->isLoadSucceeded() || !meshBlobHolder->getBlob())
		{
			m_state = loading_state_failed;
			return;
		}

		glGenVertexArrays(1, &m_renderId);
		glBindVertexArray(m_renderId);

		//generate vertexbuffer
		glGenBuffers(1, &m_vbId);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbId);
		glBufferData(GL_ARRAY_BUFFER, meshBlobHolder->m_meshDesc.vertexDataSize, (char*)meshBlobHolder->getBlob()->getData() + meshBlobHolder->m_meshDesc.vertexDataOffset, GL_STATIC_DRAW);

		//generate indexbuffer
		m_count = meshBlobHolder->m_meshDesc.indexDataSize / sizeof(unsigned int);
		glGenBuffers(1, &m_ibId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshBlobHolder->m_meshDesc.indexDataSize, (char*)meshBlobHolder->getBlob()->getData() + meshBlobHolder->m_meshDesc.indexDataOffset, GL_STATIC_DRAW);

		const auto& Layout = meshBlobHolder->m_layout;
		for (const auto& layout : Layout)
		{
			glEnableVertexAttribArray(layout.index);
			if (layout.type == GL_INT)
			{
				glVertexAttribIPointer(layout.index, layout.count, layout.type, layout.stride, (void*)(layout.start));
			}
			else if (layout.type == GL_FLOAT)
			{
				glVertexAttribPointer(layout.index, layout.count, layout.type, layout.normalized, layout.stride, (void*)(layout.start));
			}	
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);	

		m_state = loading_state_succeeded;
	}

	void Mesh::unload()
	{
		glDeleteBuffers(1, &m_vbId);
		glDeleteBuffers(1, &m_ibId);
		glDeleteVertexArrays(1, &m_renderId);
		m_state = loading_state_pending;
	}

	void Mesh::bind()
	{
		glBindVertexArray(m_renderId);
	}

	void Mesh::unbind()
	{
		glBindVertexArray(0);
	}

	void Mesh::draw()
	{
		bind();
		glDrawElements(GL_TRIANGLES, m_count, GL_UNSIGNED_INT, (void*)0);
		unbind();
	}
}