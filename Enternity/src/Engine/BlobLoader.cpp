#include "BlobLoader.h"
#include "ThreadPool.h"

namespace Enternity
{
	void BlobLoader::load(int priority)
	{
		if (priority)
		{
			ThreadPool::GetInstance().commitTask(std::bind(&BlobLoader::doLoad, this));
		}
		else
		{
			doLoad();
		}
	}
}