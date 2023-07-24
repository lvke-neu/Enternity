#include "VertexArray.h"
#include "MeshBlobHolder.h"
#include "Engine/Blob.h"
#include <glad/glad.h>

namespace Enternity
{
	VertexArray::~VertexArray()
	{
		glDeleteBuffers(1, &m_vbId);
		glDeleteBuffers(1, &m_ibId);
		glDeleteVertexArrays(1, &m_renderId);
	}

	void VertexArray::load(BlobHolder* blobHolder)
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
		glBufferData(GL_ARRAY_BUFFER, meshBlobHolder->getMeshDesc().vertexDataSize, (char*)meshBlobHolder->getBlob()->getData() + meshBlobHolder->getMeshDesc().vertexDataOffset, GL_STATIC_DRAW);

		//generate indexbuffer
		m_count = meshBlobHolder->getMeshDesc().indexDataSize / sizeof(unsigned int);
		glGenBuffers(1, &m_ibId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshBlobHolder->getMeshDesc().indexDataSize, (char*)meshBlobHolder->getBlob()->getData() + meshBlobHolder->getMeshDesc().indexDataOffset, GL_STATIC_DRAW);

		const auto& Layout = meshBlobHolder->getLayout();
		for (const auto& layout : Layout)
		{
			glEnableVertexAttribArray(layout.index);
			glVertexAttribPointer(layout.index, layout.count, layout.type, layout.normalized, layout.stride, (void*)(layout.start));
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);	

		m_state = loading_state_succeeded;
	}

	void VertexArray::unload()
	{
		glDeleteBuffers(1, &m_vbId);
		glDeleteBuffers(1, &m_ibId);
		glDeleteVertexArrays(1, &m_renderId);
		m_state = loading_state_pending;
	}

	void VertexArray::bind()
	{
		glBindVertexArray(m_renderId);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}
}