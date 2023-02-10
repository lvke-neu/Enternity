#include "Engine/Engine.h"

#include "UnitTest.h"

int main()
{
	Enternity::Engine::GetInstance().initialize();
	//**************TODO:remove**************
	UnitTest();
	//***************************************
	Enternity::Engine::GetInstance().run();
	Enternity::Engine::GetInstance().uninitialize();

	return 0;
}