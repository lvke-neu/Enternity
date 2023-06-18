#pragma once
#include <CRTDBG.H>

//assert
#ifdef DEBUG
	#define  ENTERNITY_ASSERT(expr)	_ASSERTE(expr)
#else
	#define  ENTERNITY_ASSERT(expr)	((void)0)
#endif 

// singleton
#define SINGLETON(CLASS) \
	public:\
		static CLASS& GetInstance()\
		{\
			static CLASS s_instance;\
			return s_instance; \
		}
#define PRIVATE(CLASS)\
	private: \
		CLASS() = default; \
		virtual ~CLASS() = default; \
		CLASS(const CLASS&) = default; \
		CLASS& operator=(const CLASS&) = default;

//safe delete
#define SAFE_DELETE_SET_NULL(p) \
	if((p))\
	{\
		delete p;\
		p = nullptr;\
	}


//safe delete arrat
#define DELETE_ARRAY(p) \
	delete[] p;

//check gl function
static bool Call_Gl_Function = true;
static const char* error[8] = 
{"GL_INVALID_ENUM", "GL_INVALID_VALUE", "GL_INVALID_OPERATION", "GL_STACK_OVERFLOW", "GL_STACK_UNDERFLOW", "GL_OUT_OF_MEMORY", "GL_INVALID_FRAMEBUFFER_OPERATION", "GL_CONTEXT_LOST", };
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
