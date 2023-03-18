/***************************************************************************************
Author: lvke
Date:2023/2/11 10:45
Description:
Texture
****************************************************************************************/
#pragma once
#include <vector>

namespace Enternity
{
	class Blob;
	class Texture2D
	{
	public:
		~Texture2D();
	public:
		void init(Blob* blob);
		void bind(unsigned int slot);
		void unbind();
		inline unsigned int getRenderId()
		{
			return m_renderId;
		}
	private:
		unsigned int m_renderId;
	};

	class TextureCube
	{
	public:
		~TextureCube();
	public:
		void init(const std::vector<Blob*>& blobs);
		void bind(unsigned int slot);
		void unbind();
	private:
		unsigned int m_renderId;
	};
}