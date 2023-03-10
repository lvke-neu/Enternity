#pragma once

#include <CRTDBG.H>

namespace Enternity
{
	//assert
#ifdef DEBUG
#define  ENTERNITY_ASSERT(expr)	_ASSERTE(expr)
#else
#define  ENTERNITY_ASSERT(expr)	((void)0)
#endif 



#define SINGLETON(ClassName)\
public:\
	static ClassName& GetInstance()\
	{\
		static ClassName s_instance;\
		return s_instance;\
	}\
private:\
	ClassName() = default;\
	~ClassName() = default;\
	ClassName(const ClassName&) = default;\
	ClassName& operator=(const ClassName&) = default;


#define SAFE_DELETE_SET_NULL(p) \
	if((p))\
	{\
		delete p;\
		p = nullptr;\
	}



//check gl function
	static bool Call_Gl_Function = true;
	static const char* error[8] =
	{ "GL_INVALID_ENUM", "GL_INVALID_VALUE", "GL_INVALID_OPERATION", "GL_STACK_OVERFLOW", "GL_STACK_UNDERFLOW", "GL_OUT_OF_MEMORY", "GL_INVALID_FRAMEBUFFER_OPERATION", "GL_CONTEXT_LOST", };
	static unsigned int errorCode;

#define CHECK_GL_CALL(glFunction) \
	while (glGetError() != GL_NO_ERROR);\
	glFunction;\
	errorCode = glGetError();\
	if(errorCode != GL_NO_ERROR)\
	{\
		LOG_ERROR("glFunction error:{0}", error[errorCode - 1280]);\
		ENTERNITY_ASSERT(Call_Gl_Function == false);\
	}
}

