/***************************************************************************************
Author: lvke
Date:2022/12/31 14:35
Description:
Renderer Interface
****************************************************************************************/
#pragma once
#include <glad/glad.h>
#include "Macro/Macro.h"
#include "Log/Log.h"

BEGIN_ENTERNITY

class IBindable
{
public:
	virtual void Bind(unsigned int slot = 0) const = 0;
	virtual void UnBind() const = 0;
	virtual ~IBindable() = default;
protected:
	unsigned int m_rendererId;
};



#define CHECK_GL_CALL(x) \
	while (glGetError() != GL_NO_ERROR);\
	x;\
	assert(glGetError() == GL_NO_ERROR);\

END_ENTERNITY