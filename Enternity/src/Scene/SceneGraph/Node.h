#pragma once
#include <string>
#include <vector>

namespace Enternity
{
	class Node
	{
	public:
		Node();
		virtual ~Node();
	public:
		void addToParent(Node* node);
		const std::vector<Node*>& getChilds() const;

		void setName(const std::string& name);
		const std::string& getName() const;
	private:
		std::string m_name;
		std::string m_uuid;
		Node* m_parent;

		std::vector<Node*> m_childs;
	};

	inline const std::string& Node::getName() const
	{
		return m_name;
	}

	inline const std::vector<Node*>& Node::getChilds() const
	{
		return m_childs;
	}
}