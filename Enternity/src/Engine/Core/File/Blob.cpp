#include "Blob.h"
#include <string.h>

namespace Enternity
{
	Blob::Blob(size_t length)
	{
		m_data = new char[length];
		m_length = length;
	}

	Blob::~Blob()
	{
		DELETE_ARRAY(m_data);
	}

	void Blob::copyDataFrom(void* data)
	{
		memcpy_s(m_data, m_length, data, m_length);
	}
}