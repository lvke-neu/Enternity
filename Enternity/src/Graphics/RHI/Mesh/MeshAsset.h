#pragma once
#include "Engine/Asset.h"
#include "VertexDefine.h"
#include <string>
#include <vector>

namespace Enternity
{
	class MeshAsset : public Asset
	{
		friend class Texture;
	public:
		MeshAsset(const std::string& fullPath);
		~MeshAsset();
	public:
		const std::vector<std::vector<Vertex_Positon_Normal_Texcoord>>& getVertices() const;
		const std::vector<std::vector<unsigned int>>& getIndices() const;
	private:
		virtual void doLoad() override;
	private:
		std::string m_fullPath{ "" };

		std::vector<std::vector<Vertex_Positon_Normal_Texcoord>> m_vertices;
		std::vector<std::vector<unsigned int>> m_indices;
	};

	inline const std::vector<std::vector<Vertex_Positon_Normal_Texcoord>>& MeshAsset::getVertices() const
	{
		return m_vertices;
	}

	inline const std::vector<std::vector<unsigned int>>& MeshAsset::getIndices() const
	{
		return m_indices;
	}
}

