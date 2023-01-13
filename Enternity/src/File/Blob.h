#pragma once

#include "Macro/Macro.h"

BEGIN_ENTERNITY

class Blob
{
public:
	Blob(unsigned int length)
	{
		m_Data = new char[length];
		m_Length = length;
	}
public:
	const void* GetData() const { return m_Data; }
	const unsigned int GetLength() const { return m_Length; }
private:
	void* m_Data{ nullptr };
	unsigned int m_Length{ 0 };
};

END_ENTERNITY