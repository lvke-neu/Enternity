#pragma once
#include "Engine/Asset2.h"
#include "VertexDefine.h"
#include "MeshDefine.h"
#include <string>
#include <vector>

namespace Enternity
{
	class MeshAsset : public Asset2
	{
	public:
		MeshAsset(const std::string& fullPath);
		virtual ~MeshAsset();
	public:
		const std::vector<std::vector<Vertex_Positon_Normal_Texcoord>>& getVertices() const;
		const std::vector<std::vector<unsigned int>>& getIndices() const;
		const std::vector<std::string>& getMaterials() const;
		std::vector<Layout> getLayouts() const;
		unsigned int getVertexDataSize(unsigned int location) const;
		unsigned int getIndexDataSize(unsigned int location) const;
		const std::string& getFullPath() const;
	private:
		virtual void doLoad() override;
	protected:
		std::string m_fullPath{ "" };

		std::vector<std::vector<Vertex_Positon_Normal_Texcoord>> m_vertices;
		std::vector<std::vector<unsigned int>> m_indices;
		std::vector<std::string> m_materials;
	};

	inline const std::vector<std::vector<Vertex_Positon_Normal_Texcoord>>& MeshAsset::getVertices() const
	{
		return m_vertices;
	}

	inline const std::vector<std::vector<unsigned int>>& MeshAsset::getIndices() const
	{
		return m_indices;
	}

	inline const std::vector<std::string>& MeshAsset::getMaterials() const
	{
		return m_materials;
	}

	inline std::vector<Layout> MeshAsset::getLayouts() const
	{
		return Vertex_Positon_Normal_Texcoord::layouts;
	}

	inline unsigned int MeshAsset::getVertexDataSize(unsigned int location) const
	{
		return (unsigned int)(sizeof(Vertex_Positon_Normal_Texcoord) * m_vertices[location].size());
	}

	inline unsigned int MeshAsset::getIndexDataSize(unsigned int location) const
	{
		return (unsigned int)(sizeof(unsigned int) * m_indices[location].size());
	}

	inline const std::string& MeshAsset::getFullPath() const
	{
		return m_fullPath;
	}
	
	class BasicMeshAsset : public MeshAsset
	{
	public:
		BasicMeshAsset(BasicMeshType type, const std::string& texturePath = "");
		~BasicMeshAsset();

		virtual void doLoad() override;
	private:
		std::string mapType(BasicMeshType type);
		void buildQuadMesh();
		void buildBoxMesh();
	private:
		BasicMeshType m_type;
	};
}

