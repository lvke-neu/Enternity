#pragma once
#include <vector>

namespace Enternity
{

	struct LayoutElement
	{
		LayoutElement(unsigned int _index, unsigned int _count, unsigned int _type, bool _normalized, int _stride, long long _start)
		{
			index = _index;
			count = _count;
			type = _type;
			normalized = _normalized;
			stride = _stride;
			start = _start;
		}
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
		VertexBufferLayout(const std::vector<LayoutElement>& layoutElements);
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
}
