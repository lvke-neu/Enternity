#include "Blob.h"

namespace Enternity
{
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
}