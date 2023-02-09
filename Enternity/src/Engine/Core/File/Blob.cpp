#include "Blob.h"

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
}