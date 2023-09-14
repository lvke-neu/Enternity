#include "Engine/Engine.h"

int main(int argc, const char** argv) {

	Enternity::Engine::GetInstance().initialize();
	Enternity::Engine::GetInstance().run();
	Enternity::Engine::GetInstance().uninitialize();


	return 0;
}


//#include "Scene/SceneGraph/3D/Visual3DComponent.h"
//#include <iostream>
//#include <rttr/type>
//
//using namespace Enternity;
//
//
//int main(int argc, const char** argv) {
//
//	auto type =rttr::type::get_by_name("Visual3DComponent");
//
//	return 0;
//}