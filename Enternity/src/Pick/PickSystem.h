#pragma once

namespace Enternity
{
	class PickSystem
	{
		friend class Engine;
	private:
		PickSystem();
		~PickSystem();
	public:
		int getPickEntityId();
		void setPickEntityId(int id);
	private:
		int m_pickEntityId{ -1 };
	};

	inline int PickSystem::getPickEntityId()
	{
		return m_pickEntityId;
	}

	inline void PickSystem::setPickEntityId(int id)
	{
		m_pickEntityId = id;
	}
}