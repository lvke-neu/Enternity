#pragma once

namespace Enternity
{
	class ScenePanel
	{
	public:
		void draw();
		int getSelectedEntityId() const ;
	private:
		int m_selectedEntityId{ -1 };
	};

	inline int ScenePanel::getSelectedEntityId() const
	{
		return m_selectedEntityId;
	}
}