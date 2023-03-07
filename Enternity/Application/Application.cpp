#include "Application.h"
#include "Engine.h"

#include "Engine/RuntimeModule/TestAsset/TextAsset.h"
#include "Engine/RuntimeModule/TestAsset/TextAssetLoader.h"
#include "RuntimeModule/Asset/AssetManager.h"
#include "Core/Blob/Blob.h"

namespace Enternity
{
	bool Application::Initialize()
    {
        return Engine::GetInstance().Initialize();
    }

    void Application::Finalize()
    {
		Engine::GetInstance().Finalize();
    }

    void Application::Run()
    {

		TextAssetLoader textAssetLoader;
		TextAsset textAsset("Assets/TestAssetLoader.txt", &textAssetLoader);

		AssetManager* assetManager = (AssetManager*)Engine::GetInstance().GetRuntimeModule("AssetManager");
		Blob* blob = assetManager->loadAsset(textAsset);

		std::string str((char*)blob->getData(), blob->getLength());


		TextAssetLoader textAssetLoader2;
		TextAsset textAsset2("Assets/TestAssetLoader.txt", &textAssetLoader);

		AssetManager* assetManager2 = (AssetManager*)Engine::GetInstance().GetRuntimeModule("AssetManager");
		Blob* blob2 = assetManager2->loadAsset(textAsset);

		std::string str2((char*)blob2->getData(), blob2->getLength());


		int i = 0;
		i++;

		Engine::GetInstance().Tick();
    }
}