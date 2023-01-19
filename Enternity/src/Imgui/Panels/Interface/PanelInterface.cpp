#include "PanelInterface.h"

BEGIN_ENTERNITY


IPanel::IPanel()
{
	ImguiDrawEventManager::GetInstance().RegisterEvent(this);
}

Enternity::IPanel::~IPanel()
{
	ImguiDrawEventManager::GetInstance().UnRegisterEvent(this);
}

END_ENTERNITY

