/***************************************************************************************
Author: lvke
Date:2023/1/27 21:20
Description:
Viewport2 Panel(for debug)
****************************************************************************************/
#pragma once

#include "Interface/PanelInterface.h"


BEGIN_ENTERNITY

class ViewportPanel2 : public IPanel
{
public:
	ViewportPanel2();
	virtual ~ViewportPanel2();
	virtual void ImguiDraw() override;
};

END_ENTERNITY
