#include "Engine/Engine.h"

#include "Common/UnitTest.h"
int main(int argc, const char** argv) {

	//Enternity::Engine::GetInstance().initialize();
	//Enternity::Engine::GetInstance().run();
	//Enternity::Engine::GetInstance().uninitialize();
	Enternity::Engine::GetInstance().initialize();
	UnitTest ut;
	return 0;
}


