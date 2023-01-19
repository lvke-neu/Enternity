/***************************************************************************************
Author: lvke
Date:2023/1/19 20:30
Description:
Viewport Panel
****************************************************************************************/
#pragma once

#include "Interface/PanelInterface.h"

BEGIN_ENTERNITY

class StatsPanel : public IPanel
{
public:
	StatsPanel();
	virtual ~StatsPanel();
	virtual void ImguiDraw() override;
};

END_ENTERNITY
