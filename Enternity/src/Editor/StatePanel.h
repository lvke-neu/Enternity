#pragma once

namespace Enternity
{
	class Node;
	class StatePanel
	{
	public:
		void draw();
	private:
		void treeNode(Node* node);
	};
}