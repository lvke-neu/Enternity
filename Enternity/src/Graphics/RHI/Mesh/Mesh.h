#pragma once
#include <vector>

namespace Enternity
{
	class VertexArray;
	class IndexBuffer;
	class MeshAsset;
	class Mesh
	{
	public:
		Mesh(MeshAsset* meshAsset);
		~Mesh();
		const std::vector<VertexArray*>& getVertexArraies() const;
		const std::vector <IndexBuffer*>& getIndexBuffers() const;
	private:
		std::vector<VertexArray*> m_vertexArraies{ nullptr };
		std::vector <IndexBuffer*> m_indexBuffers{ nullptr };
	};
}