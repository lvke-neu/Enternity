//#include "Engine/Engine.h"
//
//int main(int argc, const char** argv) {
//
//	Enternity::Engine::GetInstance().initialize();
//	Enternity::Engine::GetInstance().run();
//	Enternity::Engine::GetInstance().uninitialize();
//
//
//	return 0;
//}


//#include "Scene/SceneGraph/Node.h"
//
//int main(int argc, const char** argv) {
//
//	using namespace Enternity;
//	Node* rootNode = new Node;
//	rootNode->setName("Root");
//
//	for (int i = 0; i < 5; i++)
//	{
//		Node* node = new Node;
//		node->setName(std::to_string(i).c_str());
//		node->addToParent(rootNode);
//	}
//
//	return 0;
//}