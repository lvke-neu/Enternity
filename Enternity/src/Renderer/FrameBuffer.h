/***************************************************************************************
Author: lvke
Date:2023/1/8 12:26
Description:
Encapsulate  FrameBuffer
****************************************************************************************/
#pragma once

#include "Interface/BindableInterface.h"

BEGIN_ENTERNITY

class FrameBuffer : public IBindable
{
public:
	FrameBuffer(unsigned int width, unsigned int height);
	virtual ~FrameBuffer();

	virtual void Bind(unsigned int slot = 0) const override;
	virtual void UnBind() const override;

	void Rebuild(unsigned int width, unsigned int height);
	inline unsigned int GetTextureRendererId() const { return m_texRendererId; }
private:
	unsigned int m_texRendererId;
	unsigned int m_renderBufferId;

};

END_ENTERNITY
