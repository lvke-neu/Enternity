#include <iostream>
#include <memory>
#include <fstream>
#include <filesystem>
#include <string>
#include <set>

class Test
{
public:
	 Test()
	{
		 std::cout << "构造函数" << std::endl;
	}

	 ~Test()
	 {
		 std::cout << "析构函数" << std::endl;
	 }

	 Test(const Test& test)
	 {
		 std::cout << "拷贝构造函数" << std::endl;
	 }

	 Test& operator=(const Test& test)
	 {
		 std::cout << "重载=" << std::endl;
		 return *this;
	 }
};

void func(const std::vector<int>& arr)
{
	for (auto& num : arr)
	{
		
	}
}
enum treee
{
	Apple = 1,
	Peer,
	Banana
};


class Component
{
public:
	void hhahah()
	{

	}
};

std::vector<std::shared_ptr<Component>> m_components;
void funnnnc()
{

	{
		std::shared_ptr<Component> pComponent2(new Component);
		std::vector<std::shared_ptr<Component>> m_components2;
		m_components2.push_back(pComponent2);
		m_components2.clear();

	}
	

	int i = 0;
	i++;

}

#include "Node.h"
void treeNode(std::shared_ptr<Node> node)
{
	std::cout << node->get_name() << std::endl;
	for (auto node : node->m_childs)
	{
		treeNode(node);
	}
}

int main()
{

	std::shared_ptr<Node> rootNode(new Node);
	rootNode->set_name("rootnode");

	for (int i = 0; i < 5; i++)
	{
		std::shared_ptr<Node> node(new Node);
		node->set_name(std::to_string(i));

		rootNode->addChild(node);
		for (int j = 0; j < 5; j++)
		{
			std::shared_ptr<Node> node2(new Node);
			node2->set_name(std::to_string(i) + "_" + std::to_string(j));

			node->addChild(node2);
		}

	}
	

	treeNode(rootNode);
	auto node0 = rootNode->m_childs[0];
	node0->removeFromParent();
	std::cout << "==================================" << std::endl;
	treeNode(rootNode);

	getchar();

	return 0;
}

