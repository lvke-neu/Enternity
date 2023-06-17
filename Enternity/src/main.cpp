#include "Engine/ThreadPool.h"
#include "Engine/Log.h"
#include "Engine/Detail/WindowsFileAsset.h"
#include "Engine/Blob.h"

using namespace Enternity;
int main(int argc, const char** argv) {

	Log::Init();
	ThreadPool::GetInstance().initialize(4);

	WindowsFileAsset windowsFileAsset("assets/TestWindowsFileAsset.txt");
	windowsFileAsset.load();
	while (true)
	{
		if (windowsFileAsset.getLoadingState() == Asset::loading_state_succeeded)
		{
			Blob* blob = windowsFileAsset.getBlob();

			if (blob)
			{
				LOG_INFO(std::string((char*)blob->getData(), blob->getLength()));
			}

			
		}

		LOG_INFO("loading_state_pending");
	}

	ThreadPool::GetInstance().uninitialize();
	return 0;
}


