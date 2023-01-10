/***************************************************************************************
Author: lvke
Date:2022/12/31 14:26
Description:
Encapsulate  VertexBuffer
****************************************************************************************/
#pragma once

#include "Interface/BindableInterface.h"

BEGIN_ENTERNITY

class VertexBuffer : public IBindable
{
public:
	VertexBuffer() = default;
	VertexBuffer(const void* vertices, unsigned int size);
	virtual ~VertexBuffer();
	
	virtual void Bind(unsigned int slot = 0) const override;
	virtual void UnBind() const override;
};

END_ENTERNITY
