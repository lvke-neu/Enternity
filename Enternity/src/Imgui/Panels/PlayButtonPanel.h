/***************************************************************************************
Author: lvke
Date:2023/1/20 12:31
Description:
PlayButton Panel
****************************************************************************************/
#pragma once

#include "Interface/PanelInterface.h"
#include "Event/ImguiDrawEventManager.h"
#include "Renderer/Texture.h"

BEGIN_ENTERNITY

class PlayButtonPanel : public IPanel
{
public:
	PlayButtonPanel();
	~PlayButtonPanel();

	virtual void ImguiDraw() override;
private:
	Texture* m_EditorTexture{ nullptr };
	Texture* m_PlayerTexture{ nullptr };
};

END_ENTERNITY