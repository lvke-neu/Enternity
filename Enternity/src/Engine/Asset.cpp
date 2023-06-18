#include "Asset.h"
#include "ThreadPool.h"

namespace Enternity
{
	void Asset::load(int priority)
	{
		if (priority)
		{
			ThreadPool::GetInstance().commitTask(std::bind(&Asset::doLoad, this));
		}
		else
		{
			doLoad();
		}
	}
}