#include "Blob.h"
#include <string.h>

namespace Enternity
{
	Blob::Blob(size_t length)
	{
		m_data = new char[length];
		m_length = length;
	}

	Blob::Blob(const Blob& blob)
	{
		if(m_length > 0)
			delete[] m_data;

		m_length = blob.m_length;
		m_data = new char[m_length];
		memcpy_s(m_data, m_length, blob.getData(), m_length);
	}

	Blob::~Blob()
	{
		delete[] m_data;
	}
}