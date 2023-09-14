#pragma once
#include <CRTDBG.H>

//*************************************************assert*************************************************
#ifdef DEBUG
	#define  ENTERNITY_ASSERT(expr)	_ASSERTE(expr)
#else
	#define  ENTERNITY_ASSERT(expr)	((void)0)
#endif 
//********************************************************************************************************


//*************************************************singleton*************************************************
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
//********************************************************************************************************



//*************************************************delete*************************************************
#define SAFE_DELETE_SET_NULL(p) \
	if((p))\
	{\
		delete p;\
		p = nullptr;\
	}

#define DELETE_ARRAY(p) \
	delete[] p;
//********************************************************************************************************


//*************************************************check gl function**************************************
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
//********************************************************************************************************



//*************************************************get set************************************************
#define GET(TYPE, NAME)\
	TYPE get_##NAME() const\
	{\
		return m_##NAME;\
	}\

#define SET(TYPE, NAME)\
	void set_##NAME(TYPE NAME)\
	{\
		m_##NAME = NAME;\
	}

#define GET_SET(TYPE, NAME)\
	GET(TYPE, NAME);\
	SET(TYPE, NAME);
//**********************************************************************************************************


//*************************************************get type************************************************
#define GET_CLASS_NAME(NAME)\
	virtual std::string get_class_name() const\
	{\
		return #NAME;\
	}\
//********************************************************************************************************

