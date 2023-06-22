#include "IndexBuffer.h"
#include "MeshAsset.h"
#include "Common/Macro.h"
#include "Engine/Log.h"
#include <glad/glad.h>

namespace Enternity
{
	IndexBuffer::IndexBuffer(MeshAsset* meshAsset, unsigned int location)
	{
		if (meshAsset)
		{
			m_count = (unsigned int)meshAsset->getIndices()[location].size();

			CHECK_GL_CALL(glGenBuffers(1, &m_renderId));
			CHECK_GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderId));
			CHECK_GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshAsset->getIndexDataSize(location), meshAsset->getIndices()[location].data(), GL_STATIC_DRAW));
			CHECK_GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		}
	}

	IndexBuffer::~IndexBuffer()
	{
		CHECK_GL_CALL(glDeleteBuffers(1, &m_renderId));
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