/***************************************************************************************
Author: lvke
Date:
Description:
VertexBuffer
****************************************************************************************/
#pragma once
#include <vector>

namespace Enternity
{
	struct LayoutElement
	{
		unsigned int index;
		unsigned int count;
		unsigned int type;
		bool normalized;
		int stride;
		long long start;
	};

	class VertexBufferLayout
	{
	public:
		void push(const LayoutElement& layouElement)
		{
			m_layoutElements.push_back(layouElement);
		}
		std::vector<LayoutElement> getElements() const
		{
			return m_layoutElements;
		}
	private:
		std::vector<LayoutElement> m_layoutElements;
	};

	class Blob;
	class VertexBuffer
	{
	public:
		~VertexBuffer();
	public:
		void init(Blob* blob, const VertexBufferLayout& vertexBufferLayout);
		void bind();
		void unbind();
		VertexBufferLayout getVertexBufferLayout() const;
	private:
		unsigned int m_renderId;
		VertexBufferLayout m_vertexBufferLayout;
	};
}