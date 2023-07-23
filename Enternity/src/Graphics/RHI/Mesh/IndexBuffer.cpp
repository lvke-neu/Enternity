#include "IndexBuffer.h"
#include "MeshBlobHolder.h"
#include "Engine/Blob.h"
#include <glad/glad.h>

namespace Enternity
{
	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_renderId);
	}

	void IndexBuffer::load(BlobHolder* blobHolder)
	{
		MeshBlobHolder* meshBlobHolder = dynamic_cast<MeshBlobHolder*>(blobHolder);
		if (!meshBlobHolder || !meshBlobHolder->isLoadSucceeded() || !meshBlobHolder->getBlob())
		{
			m_state = loading_state_failed;
			return;
		}

		m_count = meshBlobHolder->getMeshDesc().indexDataSize / sizeof(unsigned int);

		glGenBuffers(1, &m_renderId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshBlobHolder->getMeshDesc().indexDataSize, (char*)meshBlobHolder->getBlob()->getData() + meshBlobHolder->getMeshDesc().indexDataOffset, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		m_state = loading_state_succeeded;
	}

	void IndexBuffer::unload()
	{
		glDeleteBuffers(1, &m_renderId);
		m_state = loading_state_pending;
	}

	void IndexBuffer::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderId);
	}

	void IndexBuffer::unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}