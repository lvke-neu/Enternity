#include "Asset.h"
#include "ThreadPool.h"

namespace Enternity
{
	void Asset::load(LoadingMode mode)
	{
		if (mode == Sync)
		{
			doLoad();
		}
		else
		{
			ThreadPool::GetInstance().commitTask(std::bind(&Asset::doLoad, this));
		}
	}
}