#pragma once

#include <string>
#include <memory>
#include <vector>
#define GET(TYPE, NAME)\
	TYPE get_##NAME() const\
	{\
		return m_##NAME;\
	}\

#define SET(TYPE, NAME)\
	void set_##NAME(TYPE NAME)\
	{\
		m_##NAME = NAME;\
	}

#define GET_SET(TYPE, NAME)\
	GET(TYPE, NAME);\
	SET(TYPE, NAME);

class Node
{
public:
	Node();
	virtual ~Node();
public:
	GET(std::string, uuid);
	GET_SET(std::string, name);
public:
	void addChild(std::shared_ptr<Node> child);
	void removeChild(std::shared_ptr<Node> child);
	void removeFromParent();
public:
	std::shared_ptr<Node> m_parent;
	std::vector<std::shared_ptr<Node>> m_childs;
private:
	std::string m_uuid;
	std::string m_name;

};

