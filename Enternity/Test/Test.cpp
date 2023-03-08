#include "Test.h"
#include "TestAsset/TextAsset.h"
#include "TestAsset/TextAssetLoader.h"
#include "RuntimeModule/Asset/AssetManager.h"
#include "Engine/Engine.h"
#include "Core/Blob/Blob.h"

namespace Enternity
{
	TextAssetLoader textAssetLoader;
	TextAsset textAsset("Assets/TestAssetLoader.txt", &textAssetLoader);

	TextAssetLoader textAssetLoader2;
	TextAsset textAsset2("Assets/TestAssetLoader.txt", &textAssetLoader);

	void Test::Initialize()
	{
		AssetManager* assetManager = (AssetManager*)Engine::GetInstance().GetRuntimeModule("AssetManager");
		assetManager->loadAsset(textAsset);
	}

	void Test::Tick()
	{
		static bool flag1 = false;
		if (textAsset.getBlob())
		{
			if (!flag1)
			{
				printf("textAsset1 load finish\n");
				flag1 = true;
			}
			
			static bool flag2 = false;
			std::string str((char*)textAsset.getBlob()->getData(), textAsset.getBlob()->getLength());
			AssetManager* assetManager = (AssetManager*)Engine::GetInstance().GetRuntimeModule("AssetManager");
			assetManager->loadAsset(textAsset2);
			if (textAsset2.getBlob())
			{
				if (!flag2)
				{
					printf("textAsset2 load finish\n");
					flag2 = true;
				}
				
			}

			int i = 0;
			i++;
		}
	}
}
