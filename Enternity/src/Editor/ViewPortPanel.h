#pragma once

namespace Enternity
{
	class ViewPortPanel
	{
	public:
		void draw();
	private:
		void onViewPortResize();
	private:
		unsigned int m_width = 0;
		unsigned int m_height = 0;
	};
}