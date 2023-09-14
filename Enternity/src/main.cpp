#include "Engine/Engine.h"

int main(int argc, const char** argv) {

	Enternity::Engine::GetInstance().initialize();
	Enternity::Engine::GetInstance().run();
	Enternity::Engine::GetInstance().uninitialize();


	return 0;
}


//#include <iostream>
//#include "Scene/SceneGraph/Node.h"
//using namespace Enternity;
//
//
//int main(int argc, const char** argv) {
//
//
//	return 0;
//}