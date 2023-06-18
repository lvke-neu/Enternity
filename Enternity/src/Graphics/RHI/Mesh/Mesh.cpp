#include "Mesh.h"
#include "MeshAsset.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Common/Macro.h"

namespace Enternity
{
	Mesh::Mesh(MeshAsset* meshAsset)
	{
		m_vertexBuffer = new VertexBuffer;
		m_vertexArray = new VertexArray;
		m_indexBuffer = new IndexBuffer;

		if (meshAsset)
		{
			//TODO: init vb, va, ib
		}

		//TODO: remove
		if (meshAsset)
		{
			m_vertices = meshAsset->getVertices();
			m_indices = meshAsset->getIndices();
		}
		
	}

	Mesh::~Mesh()
	{
		SAFE_DELETE_SET_NULL(m_vertexBuffer);
		SAFE_DELETE_SET_NULL(m_vertexArray);
		SAFE_DELETE_SET_NULL(m_indexBuffer);
	}
}