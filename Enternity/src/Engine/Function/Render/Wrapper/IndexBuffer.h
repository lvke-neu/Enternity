/***************************************************************************************
Author: lvke
Date:
Description:
IndexBuffer : default unsigned int type
****************************************************************************************/
#pragma once
#include "Core/Basic/Macro.h"

namespace Enternity
{
	class Blob;
	class IndexBuffer
	{
		friend class RenderWrapper;
		PRIVATE(IndexBuffer);
	private:
		void Destroy();

	public:
		void init(Blob* blob);
		void bind();
		void unbind();
	private:
		unsigned int m_renderId;
		unsigned int m_count;
	};
}