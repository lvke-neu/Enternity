#pragma once

namespace Enternity
{
	class UniformBuffer
	{
	public:
		UniformBuffer();
		~UniformBuffer();
	public:
		void modify(const void* data, unsigned int size, unsigned int bindPoint);
	private:
		unsigned int m_renderId;
	};
}