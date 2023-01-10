#include "Entity.h"


BEGIN_ENTERNITY

Entity::Entity(const std::string& name)
{
	m_Name = name == "" ? "UnKnown Name" : name;
	auto& registry = SceneManager::s_Registry;
	m_EntityUid = registry.create();
}

END_ENTERNITY


