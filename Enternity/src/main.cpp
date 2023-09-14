#include "Engine/Engine.h"

int main(int argc, const char** argv) {

	Enternity::Engine::GetInstance().initialize();
	Enternity::Engine::GetInstance().run();
	Enternity::Engine::GetInstance().uninitialize();


	return 0;
}


//#include <iostream>
//#include "Scene/Scene3D.h"
//using namespace Enternity;
//
//
//int main(int argc, const char** argv) {
//
//	Scene* sc3d = new Scene3D;
//
//	delete sc3d;
//
//	return 0;
//}