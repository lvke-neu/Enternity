#include "Entity.h"


BEGIN_ENTERNITY

Entity::Entity(entt::registry* registry, const std::string& name)
{
	m_pSceneRegistry = registry;
	m_Name = name == "" ? "UnKnown Name" : name;
	m_EntityUid = (*m_pSceneRegistry).create();
}

END_ENTERNITY


