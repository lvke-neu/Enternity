/***************************************************************************************
Author: lvke
Date:
Description:
Blob
****************************************************************************************/
#pragma once
#include "Core/Basic/Macro.h"

namespace Enternity
{
	class Blob
	{ 
	public:
		static Blob* New(unsigned int length);
		inline void* getData();
		inline unsigned int getLength();
	private:
		Blob(unsigned int length);
		~Blob();
	private:
		void* m_data{ nullptr };
		unsigned int m_length{ 0 };
	};

	Blob::Blob(unsigned int length)
	{
		m_data = new char[length];
	}

	Blob::~Blob()
	{
		DELETE_ARRAY(m_data);
	}

	Blob* Blob::New(unsigned int length)
	{
		return new Blob(length);
	}

	inline void* Blob::getData()
	{
		return m_data;
	}

	inline unsigned int Blob::getLength()
	{
		return m_length;
	}
}