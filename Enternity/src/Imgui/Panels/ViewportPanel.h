/***************************************************************************************
Author: lvke
Date:2023/1/19 18:52
Description:
Viewport Panel
****************************************************************************************/
#pragma once

#include "Interface/PanelInterface.h"
#include "../ImguiImpl/ImGuizmo.h"

BEGIN_ENTERNITY

struct MyVec2f 
{
	float x;
	float y;
};

class ViewportPanel : public IPanel
{
public:
	ViewportPanel();
	virtual ~ViewportPanel();
	virtual void ImguiDraw() override;
	
	inline int GetHoverEntityId()
	{
		return m_MousePickPixelEntityId;
	}

	void SetGizmoType(int type)
	{
		m_GizmoType = type;
	}
	int GeGizmoType()
	{
		return m_GizmoType;
	}


	void LoadScene();
private:
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_GizmoType = 0;
	int m_MousePickPixelEntityId = -1;
	MyVec2f m_ViewportBounds[2];

	std::string m_ScenePath = "";
};

END_ENTERNITY
