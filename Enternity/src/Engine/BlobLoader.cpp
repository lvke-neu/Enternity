#include "BlobLoader.h"
#include "BlobHolder.h"

namespace Enternity
{
	BlobLoader::BlobLoader(const char* storagePath) :
		m_storagePath(storagePath)
	{

	}

	BlobLoader::~BlobLoader()
	{

	}

	BlobHolder* BlobLoader::createBlobHolder(const char* path)
	{
		return new BlobHolder(this, path);
	}
}