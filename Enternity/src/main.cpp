#include "Engine/Engine.h"

#include "UnitTest.h"

void NotifyFinish()
{
	Vector4f::DARK_COLOR = Vector4f::RED_COLOR;
	LOG_INFO("finish");
}

int main()
{
	Enternity::Engine::GetInstance().initialize();
	//**************TODO:remove**************
	UnitTest(NotifyFinish);
	//***************************************
	Enternity::Engine::GetInstance().run();
	Enternity::Engine::GetInstance().uninitialize();

	return 0;
}