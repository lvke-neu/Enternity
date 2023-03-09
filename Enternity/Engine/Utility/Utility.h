#pragma once

namespace Enternity
{

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

	class Blob;
	Blob* ReadFile(const char* filePath);
}