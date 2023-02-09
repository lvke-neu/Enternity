/***************************************************************************************
Author: lvke
Date:
Description:
VertexArray
****************************************************************************************/
#pragma once
#include "Core/Basic/Macro.h"

namespace Enternity
{
	class VertexBuffer;
	class VertexArray
	{
		friend class RenderWrapper;
		PRIVATE(VertexArray);
	private:
		void Destroy();

	public:
		void init(VertexBuffer* vertexBuffer);
		void bind();
		void unbind();
	private:
		unsigned int m_renderId;
	};
}