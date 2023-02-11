/***************************************************************************************
Author: lvke
Date:2023/2/11 10:45
Description:
Texture
****************************************************************************************/
#pragma once
#include "Core/Basic/Macro.h"
#include <vector>

namespace Enternity
{
	class Blob;
	class Texture2D
	{
		friend class RenderWrapper;
		PRIVATE(Texture2D);
	private:
		void Destroy();
	public:
		void init(Blob* blob);
		void bind(unsigned int slot);
		void unbind();
	private:
		unsigned int m_renderId;
	};

	class TextureCube
	{
		friend class RenderWrapper;
		PRIVATE(TextureCube);
	private:
		void Destroy();
	public:
		void init(const std::vector<Blob*>& blobs);
		void bind(unsigned int slot);
		void unbind();
	private:
		unsigned int m_renderId;
	};
}