#include "UnitTest.h"
#include "Engine/Engine.h"
#include "Graphics/GraphicsSystem.h"
#include "Graphics/RHI/Texture/TextureProvider.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Graphics/RHI/Texture/TextureAsset.h"
#include "Graphics/RHI/Renderer/RendererProvider.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Renderer/RendererAsset.h"
#include "Graphics/RHI/Mesh/MeshProvider.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Mesh/MeshAsset.h"
#include "Engine/Log.h"
#include "Engine/Event/EventSystem.h"

using namespace Enternity;
void UnitTest::Test()
{
	Mesh* mesh = Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshSync("assets/models/2nrtbod1out/2nrtbod1out.obj");
	Texture* texture = Engine::GetInstance().getGraphicsSystem()->getTextureProvider()->getTexture("assets/textures/skybox.jpeg");
	Renderer* renderer = Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRenderer("assets/shaders/Phong.vert", "assets/shaders/Phong.frag");

	//MeshAsset ma("assets/models/2nrtbod1out/2nrtbod1out.obj");
	//ma.load();
	//while (true)
	//{
	//	if (ma.getLoadingState() == Asset::loading_state_succeeded)
	//	{
	//		Mesh mesh(&ma);
	//		int i = 0;
	//		i++;
	//	}
	//}


	SAFE_DELETE_SET_NULL(mesh);
	SAFE_DELETE_SET_NULL(texture);
	SAFE_DELETE_SET_NULL(renderer);
}

UnitTest::UnitTest()
{
	Event event{ EventType::WindowResize, std::bind(&UnitTest::callbackFunc, this, std::placeholders::_1) };
	Engine::GetInstance().getEventSystem()->registerEvent(event);

	//event = Event{ EventType::Tick, std::bind(&UnitTest::callbackFunc2, this, std::placeholders::_1) };
	//Engine::GetInstance().getEventSystem()->registerEvent(event);

	event = Event{ EventType::KeyPressed, std::bind(&UnitTest::callbackFunc3, this, std::placeholders::_1) };
	Engine::GetInstance().getEventSystem()->registerEvent(event);

	event = Event{ EventType::KeyReleased, std::bind(&UnitTest::callbackFunc4, this, std::placeholders::_1) };
	Engine::GetInstance().getEventSystem()->registerEvent(event);	
	
	event = Event{ EventType::MousePressed, std::bind(&UnitTest::callbackFunc5, this, std::placeholders::_1) };
	Engine::GetInstance().getEventSystem()->registerEvent(event);

	event = Event{ EventType::MouseReleased, std::bind(&UnitTest::callbackFunc6, this, std::placeholders::_1) };
	Engine::GetInstance().getEventSystem()->registerEvent(event);

	event = Event{ EventType::MouseMoved, std::bind(&UnitTest::callbackFunc7, this, std::placeholders::_1) };
	Engine::GetInstance().getEventSystem()->registerEvent(event);
}

void  UnitTest::callbackFunc(void* data)
{
	WindowSize size = *(WindowSize*)data;
	LOG_INFO("callbackFunc" + std::to_string(size.width) + "," + std::to_string(size.height));
}

void  UnitTest::callbackFunc2(void* data)
{
	LOG_INFO("callbackFunc2" + std::to_string(*(float*)data));
}


void  UnitTest::callbackFunc3(void* data)
{
	LOG_INFO("callbackFunc3" + std::to_string(*(int*)data));
}

void  UnitTest::callbackFunc4(void* data)
{
	LOG_INFO("callbackFunc4" + std::to_string(*(int*)data));
}

void  UnitTest::callbackFunc5(void* data)
{
	Mouse mouse = *(Mouse*)data;
	LOG_INFO("callbackFunc5" + std::to_string((int)mouse.code) + "," + std::to_string(mouse.x) + "," + std::to_string(mouse.x));
}

void  UnitTest::callbackFunc6(void* data)
{
	Mouse mouse = *(Mouse*)data;
	LOG_INFO("callbackFunc6" + std::to_string((int)mouse.code) + "," + std::to_string(mouse.x) + "," + std::to_string(mouse.x));
}

void  UnitTest::callbackFunc7(void* data)
{
	Mouse mouse = *(Mouse*)data;
	LOG_INFO("callbackFunc7" + std::to_string((int)mouse.code) + "," + std::to_string(mouse.x) + "," + std::to_string(mouse.x));
}