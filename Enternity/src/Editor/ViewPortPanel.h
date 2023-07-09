#pragma once

namespace Enternity
{
	class ViewPortPanel
	{
	public:
		void draw();
	private:
		void onViewPortResize();
		void onSelectEntityInScene();
		void onSelectEntityInPanel();
	private:
		unsigned int m_width = 0;
		unsigned int m_height = 0;

		unsigned int m_gizmoOperation = 0;
	};
}