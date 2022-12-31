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
	VertexBuffer(const void* vertices, unsigned int size);
	virtual ~VertexBuffer();
	
	virtual void Bind() const override;
	virtual void UnBind() const override;
};

END_ENTERNITY
