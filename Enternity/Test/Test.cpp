#include "Test.h"
#include "TestAsset/TextAsset.h"
#include "RuntimeModule/Asset/AssetManager.h"
#include "Engine/Engine.h"
#include "Core/Blob/Blob.h"

namespace Enternity
{

	TextAsset textAsset;


	void Test::Initialize()
	{
		textAsset.setPath("Assets/TestAssetLoader.txt");
		AssetManager* assetManager = (AssetManager*)Engine::GetInstance().GetRuntimeModule("AssetManager");
		assetManager->loadAsset(textAsset);
	}

	void Test::Tick()
	{
		//static bool flag1 = false;
		//if (textAsset.getBlob())
		//{
		//	if (!flag1)
		//	{
		//		printf("textAsset1 load finish\n");
		//		flag1 = true;
		//	}
		//
		//	int i = 0;
		//	i++;
		//}
	}
}
