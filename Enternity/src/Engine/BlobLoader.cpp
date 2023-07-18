#include "BlobLoader.h"
#include "BlobHolder.h"

namespace Enternity
{
	BlobLoader::BlobLoader(const std::string& storagePath) :
		m_storagePath(storagePath)
	{

	}

	BlobLoader::~BlobLoader()
	{

	}

	BlobHolder* BlobLoader::createBlobHolder(const std::string& path)
	{
		return new BlobHolder(this, path);
	}
}