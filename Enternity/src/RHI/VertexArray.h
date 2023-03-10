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
	class VertexArray
	{
	public:
		~VertexArray();
	public:
		void init(VertexBuffer* vertexBuffer);
		void bind();
		void unbind();
	private:
		unsigned int m_renderId;
	};
}