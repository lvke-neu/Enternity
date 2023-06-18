#include "Engine/Engine.h"

int main(int argc, const char** argv) {

	Enternity::Engine::GetInstance().initialize();
	Enternity::Engine::GetInstance().run();
	Enternity::Engine::GetInstance().uninitialize();

	//WindowsFileAsset windowsFileAsset("assets/TestWindowsFileAsset.txt");
	//windowsFileAsset.load(Asset::LoadingMode::Sync);

	//LOG_INFO("hahaha");
	//while (true)
	//{
	//	if (windowsFileAsset.getLoadingState() == Asset::loading_state_succeeded)
	//	{
	//		Blob* blob = windowsFileAsset.getBlob();

	//		if (blob)
	//		{
	//			LOG_INFO(std::string((char*)blob->getData(), blob->getLength()));
	//		}

	//		
	//	}

	//	LOG_INFO("loading_state_pending");
	//}

	return 0;
}


