#include "SimpleTriangleScene.h"
#include "Core/Reflection/Reflection.h"

#include"Core/Log/Log.h"

namespace Enternity
{
	REGISTER_CLASS(IScene, "SimpleTriangleScene", SimpleTriangleScene);

	void SimpleTriangleScene::Initialize()  
	{

	}

	void SimpleTriangleScene::Finalize()  
	{

	}

	void SimpleTriangleScene::Tick(float deltaTime)  
	{
		LOG_INFO("SimpleTriangleScene");
	}
}