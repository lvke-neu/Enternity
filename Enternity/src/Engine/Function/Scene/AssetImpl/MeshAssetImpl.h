/***************************************************************************************
Author: lvke
Date:2023/2/18 17:12
Description:
MeshAssetImpl
****************************************************************************************/
#pragma once
#include "Core/Asset/Asset.h"

namespace Enternity
{
	class IEvent;
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;
	class MeshAssetImpl
	{
	public:
		MeshAssetImpl();
		~MeshAssetImpl();
		void load(const std::string& mshFilePath);
		void unLoad();
		
		std::vector<VertexArray*>& getVertexArraies();
		std::vector<IndexBuffer*>& getIndexBuffers();
	protected:
		void loadImpl(IEvent* event);
	private:
		Asset m_meshAsset;

		std::vector<VertexArray*> m_vertexArraies;
		std::vector<VertexBuffer*> m_vertexbuffers;
		std::vector<IndexBuffer*> m_indexbuffers;
	};
}