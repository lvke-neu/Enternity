/***************************************************************************************
Author: lvke
Date:
Description:
VertexBuffer
****************************************************************************************/
#pragma once
#include "Core/Basic/Macro.h"
#include <vector>

namespace Enternity
{
	struct LayouElement
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
		void push(const LayouElement& layouElement)
		{
			m_layoutElements.push_back(layouElement);
		}
		std::vector<LayouElement> getElements() const
		{
			return m_layoutElements;
		}
	private:
		std::vector<LayouElement> m_layoutElements;
	};


	class Blob;
	class VertexBuffer
	{
		friend class RenderWrapper;
		PRIVATE(VertexBuffer);
	private:
		void Destroy();

	public:
		void setData(Blob* blob);
		void bind();
		void unbind();
	private:
		unsigned int m_renderId;
	};
}