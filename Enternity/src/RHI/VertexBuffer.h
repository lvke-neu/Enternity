/***************************************************************************************
Author: lvke
Date:
Description:
VertexBuffer
****************************************************************************************/
#pragma once

namespace Enternity
{
	class Blob;
	class VertexBuffer
	{
	public:
		~VertexBuffer();
	public:
		void init(Blob* blob);
		void bind();
		void unbind();
	private:
		unsigned int m_renderId;
	};

}