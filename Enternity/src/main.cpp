#include "Engine/Engine.h"

int main()
{
	Enternity::Engine::GetInstance().initialize();
	Enternity::Engine::GetInstance().run();
	Enternity::Engine::GetInstance().uninitialize();

	return 0;
}