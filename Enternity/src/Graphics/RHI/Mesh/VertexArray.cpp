#include "VertexArray.h"
#include "MeshAsset.h"
#include "Common/Macro.h"
#include "Engine/Log.h"
#include <glad/glad.h>

namespace Enternity
{
	VertexArray::VertexArray(MeshAsset* meshAsset, unsigned int location)
	{
		if (meshAsset)
		{
			CHECK_GL_CALL(glGenVertexArrays(1, &m_renderId));
			CHECK_GL_CALL(glBindVertexArray(m_renderId));

			//generate vertexbuffer
			glGenBuffers(1, &m_vbId);
			CHECK_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbId));
			CHECK_GL_CALL(glBufferData(GL_ARRAY_BUFFER, meshAsset->getVertexDataSize(location), meshAsset->getVertices()[location].data(), GL_STATIC_DRAW));

			const auto& layouts = meshAsset->getLayouts();
			for (const auto& layout : layouts)
			{
				CHECK_GL_CALL(glEnableVertexAttribArray(layout.index));
				CHECK_GL_CALL(glVertexAttribPointer(layout.index, layout.count, layout.type, layout.normalized, layout.stride, (void*)(layout.start)));
			}

			CHECK_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));

			CHECK_GL_CALL(glBindVertexArray(0));
		}
	}

	void VertexArray::bind()
	{
		CHECK_GL_CALL(glBindVertexArray(m_renderId));
	}

	void VertexArray::unbind()
	{
		CHECK_GL_CALL(glBindVertexArray(0));
	}

	VertexArray::~VertexArray()
	{
		CHECK_GL_CALL(glDeleteBuffers(1, &m_vbId));
		CHECK_GL_CALL(glDeleteVertexArrays(1, &m_renderId));
	}
}