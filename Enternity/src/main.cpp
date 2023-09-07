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


#include "Scene/SceneGraph/Node.h"
#include <iostream>

using namespace Enternity;

void treeNode(Node* node)
{
	std::cout << node->get_name() << std::endl;

	for (auto child : node->get_childs())
	{
		treeNode(child);
	}
}

int main(int argc, const char** argv) {

	
	Node* rootNode = new Node;
	rootNode->set_name("Root");


	for (int i = 0; i < 5; i++)
	{
		Node* node = new Node;
		node->set_name(std::to_string(i).c_str());
		node->addToParent(rootNode);

		for (int j = 0; j < 5; j++)
		{
			Node* node2 = new Node;
			node2->set_name(std::to_string(i) + "_" + std::to_string(j));
			node2->addToParent(node);
		}
	}
	treeNode(rootNode);

	std::cout << "==========================================" << std::endl;


	treeNode(rootNode);

	return 0;
}