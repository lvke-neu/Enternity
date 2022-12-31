/***************************************************************************************
Author: lvke
Date:2022/12/31 15:05
Description:
Encapsulate  IndexBuffer
****************************************************************************************/
#pragma once

#include "Interface/RendererInterface.h"

BEGIN_ENTERNITY

class IndexBuffer : public IRenderer
{
public:
	IndexBuffer(const unsigned int* indices, unsigned int count);
	~IndexBuffer();

	inline unsigned int GetCount() { return m_count; }
	virtual void Bind() const override;
	virtual void UnBind() const override;
private:
	unsigned int m_count;
};

END_ENTERNITY
