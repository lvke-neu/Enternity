#pragma once
#include <vector>
#include <string>

namespace Enternity
{
	class VertexArray;
	class IndexBuffer;
	class MeshAsset;
	class Texture;
	class Mesh
	{
	public:
		Mesh(MeshAsset* meshAsset);
		~Mesh();
		const std::vector<VertexArray*>& getVertexArraies() const;
		const std::vector <IndexBuffer*>& getIndexBuffers() const;
		const std::vector <Texture*>& getTextures() const;
		const std::string& getFullPath() const;
	private:
		std::vector<VertexArray*> m_vertexArraies{ nullptr };
		std::vector <IndexBuffer*> m_indexBuffers{ nullptr };
		std::vector <Texture*> m_textures{ nullptr };

		std::string m_fullPath{ "" };
	};
}