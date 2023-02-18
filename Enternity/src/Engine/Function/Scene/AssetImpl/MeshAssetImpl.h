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
		
		inline VertexArray* getVertexArray();
		inline IndexBuffer* getIndexBuffer();
	protected:
		void loadImpl(IEvent* event);
	private:
		Asset m_meshAsset;

		VertexArray* m_vertexArray{ nullptr };
		VertexBuffer* m_vertexbuffer{ nullptr };
		IndexBuffer* m_indexbuffer{ nullptr };
	};

	inline VertexArray* MeshAssetImpl::getVertexArray()
	{
		return m_vertexArray;
	}

	inline IndexBuffer* MeshAssetImpl::getIndexBuffer()
	{
		return m_indexbuffer;
	}
}