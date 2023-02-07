#include "Engine/Core/ExecutionTimer/ExecutionTimer.h"
#include "Engine/Core/ThreadPool/ThreadPool.h"

using namespace Enternity;
int main()
{
	Log::Init();


	ThreadPool threadPool(4);

	LOG_INFO("after threadpool start");
	while (true);
	return 0;
}