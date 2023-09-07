#pragma once

namespace Enternity
{
	class Node;
	class StatePanel
	{
	public:
		StatePanel();
	public:
		void draw();
	private:
		void treeNode(Node* node);
	private:
		Node* m_rootNode;
	};
}