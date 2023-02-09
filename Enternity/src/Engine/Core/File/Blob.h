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
		inline void* getData() const;
		inline unsigned int getLength() const;
	private:
		Blob(unsigned int length);
		~Blob();
	private:
		void* m_data{ nullptr };
		unsigned int m_length{ 0 };
	};

	inline void* Blob::getData()
	{
		return m_data;
	}

	inline unsigned int Blob::getLength()
	{
		return m_length;
	}

	inline void* Blob::getData() const
	{
		return m_data;
	}

	inline unsigned int Blob::getLength() const
	{
		return m_length;
	}
}