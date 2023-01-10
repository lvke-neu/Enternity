#include "ImguiDrawEventManager.h"

BEGIN_ENTERNITY

void ImguiDrawEventManager::NotifyImguiDraw()
{
	for (auto& event : m_events)
	{
		if (dynamic_cast<ImguiDrawEvent*>(event))
		{
			dynamic_cast<ImguiDrawEvent*>(event)->ImguiDraw();
		}
	}
}

END_ENTERNITY