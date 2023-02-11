#include "Engine/Engine.h"

#include "UnitTest.h"

std::vector<Blob*> s_datas;
void NotifyFinish(std::vector<Blob*>& datas)
{
	//Vector4f::DARK_COLOR = Vector4f::BLUE_COLOR;

	//std::vector<Texture2D*> textures;
	//textures.resize(100);
	//for (int i = 0; i < 100; ++i)
	//{
	//	textures[0] = RenderWrapper::Create<Texture2D>();
	//	textures[0]->init(datas[i]);
	//}
	//for (int i = 0; i < 100; ++i)
	//{
	//	SAFE_DELETE_SET_NULL(datas[i]);
	//	RenderWrapper::Destroy(textures[i]);
	//}
	//LOG_INFO("finish");
	s_datas = datas;
}

void loop()
{
	while (s_datas.size() != 100)
	{
		LOG_INFO("reading");
	}

	LOG_INFO("read finish");
	std::vector<Texture2D*> textures;
	textures.resize(100);
	for (int i = 0; i < 100; ++i)
	{
		textures[i] = RenderWrapper::Create<Texture2D>();
		textures[i]->init(s_datas[i]);
	}
	LOG_INFO("texture generate finish");
}

int main()
{
	Enternity::Engine::GetInstance().initialize();
	//**************TODO:remove**************
	UnitTest(NotifyFinish);
	loop();
	//***************************************
	Enternity::Engine::GetInstance().run();
	Enternity::Engine::GetInstance().uninitialize();

	return 0;
}