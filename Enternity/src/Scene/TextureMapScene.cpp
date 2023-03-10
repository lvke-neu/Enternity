#include "TextureMapScene.h"
#include "Core/Reflection/Reflection.h"

#include"Core/Log/Log.h"

namespace Enternity
{
	REGISTER_CLASS(IScene, "TextureMapScene", TextureMapScene);

	void TextureMapScene::Initialize()
	{

	}

	void TextureMapScene::Finalize()
	{

	}

	void TextureMapScene::Tick(float deltaTime)
	{
		LOG_INFO("TextureMapScene");
	}
}