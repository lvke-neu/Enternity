/***************************************************************************************
Author: lvke
Date:2022/12/31 15:05
Description:
Encapsulate  IndexBuffer
****************************************************************************************/
#pragma once

#include "Interface/BindableInterface.h"

BEGIN_ENTERNITY

class IndexBuffer : public IBindable
{
public:
	IndexBuffer() = default;
	IndexBuffer(const unsigned int* indices, unsigned int count);
	virtual ~IndexBuffer();

	inline unsigned int GetCount() { return m_count; }
	virtual void Bind(unsigned int slot = 0) const override;
	virtual void UnBind() const override;
private:
	unsigned int m_count;
};

END_ENTERNITY
