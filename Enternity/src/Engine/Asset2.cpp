#include "Asset2.h"
#include "ThreadPool.h"

namespace Enternity
{
	void Asset2::load(int priority)
	{
		if (priority)
		{
			ThreadPool::GetInstance().commitTask(std::bind(&Asset2::doLoad, this));
		}
		else
		{
			doLoad();
		}
	}
}