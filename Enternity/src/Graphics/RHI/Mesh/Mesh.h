#pragma once

//TODO: remove
#include "VertexDefine.h"
#include <vector>

namespace Enternity
{
	class VertexBuffer;
	class VertexArray;
	class IndexBuffer;
	class MeshAsset;
	class Mesh
	{
	public:
		Mesh(MeshAsset* meshAsset);
		~Mesh();
	private:
		VertexBuffer* m_vertexBuffer{ nullptr };
		VertexArray* m_vertexArray{ nullptr };
		IndexBuffer* m_indexBuffer{ nullptr };

		std::vector<std::vector<Vertex_Positon_Normal_Texcoord>> m_vertices;
		std::vector<std::vector<unsigned int>> m_indices;
	};
}