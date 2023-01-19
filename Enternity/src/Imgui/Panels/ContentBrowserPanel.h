/***************************************************************************************
Author: lvke
Date:2023/1/12 20:55
Description:
ContentBrowser Panel
****************************************************************************************/
#pragma once

#include "Interface/PanelInterface.h"
#include "Event/ImguiDrawEventManager.h"
#include <filesystem>
#include "Renderer/Texture.h"

BEGIN_ENTERNITY

class ContentBrowserPanel : public IPanel
{

public:
	ContentBrowserPanel();
	~ContentBrowserPanel();

	virtual void ImguiDraw() override;
private:
	std::filesystem::path m_Path;
	Texture* m_FileTexture{ nullptr };
	Texture* m_DirectoryTexture{ nullptr };
};

END_ENTERNITY