#include "Engine/Engine.h"

int main(int argc, const char** argv) {

	Enternity::Engine::GetInstance().initialize();
	Enternity::Engine::GetInstance().run();
	Enternity::Engine::GetInstance().uninitialize();


	return 0;
}


//#include "Scene/SceneGraph/3D/Node3D.h"


//class hhh
//{
//public:
//	int m_num = 0;
//};
//
//int main(int argc, const char** argv) {
//
//	hhh* h = new hhh;
//	
//	auto p = &(h->m_num);
//
//	return 0;
//}