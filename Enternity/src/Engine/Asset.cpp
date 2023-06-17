#include "Asset.h"
#include "ThreadPool.h"

namespace Enternity
{
	void Asset::load()
	{
		ThreadPool::GetInstance().commitTask(std::bind(&Asset::doLoad, this));
	}
}