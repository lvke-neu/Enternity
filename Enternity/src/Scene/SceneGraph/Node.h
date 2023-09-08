#pragma once
#include "Common/Macro.h"
#include <vector>
#include <string>
#include <memory>

namespace Enternity
{
	class Node
	{
	public:
		Node();
		virtual ~Node();
	public:
		GET(std::string, uuid);
		GET_SET(std::string, name);
		GET(std::vector<std::shared_ptr<Node>>, childs);
	public:
		void addChild(std::shared_ptr<Node> child);
		void removeChild(std::shared_ptr<Node> child);
		void removeFromParent();
	private:
		std::string m_uuid;
		std::string m_name;
		std::shared_ptr<Node> m_parent;
		std::vector<std::shared_ptr<Node>> m_childs;
	};
}
