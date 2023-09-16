#include "Engine/Engine.h"

int main(int argc, const char** argv) {

	Enternity::Engine::GetInstance().initialize();
	Enternity::Engine::GetInstance().run();
	Enternity::Engine::GetInstance().uninitialize();


	return 0;
}


//#include "Scene/SceneGraph/3D/Node3D.h"
//
//using namespace Enternity;
//
//
//int main(int argc, const char** argv) {
//
//	Node* node = new Node;
//	ENTERNITY_ASSERT(dynamic_cast<Node3D*>(node));
//	auto p = (Node3D*)(node);
//
//	return 0;
//}