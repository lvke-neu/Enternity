/***************************************************************************************
Author: lvke
Date:
Description:
VertexArray
****************************************************************************************/
#pragma once

namespace Enternity
{
	class VertexBuffer;
	class VertexBufferLayout;
	class VertexArray
	{
	public:
		~VertexArray();
	public:
		void init(VertexBuffer* vertexBuffer, VertexBufferLayout* vertexBufferLayout);
		void bind();
		void unbind();
	private:
		unsigned int m_renderId;
	};
}