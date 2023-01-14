#include "Entity.h"
#include "../Component/Component.h"

BEGIN_ENTERNITY

Entity::Entity(entt::registry* registry, const std::string& name)
{
	m_pSceneRegistry = registry;
	m_EntityUid = (*m_pSceneRegistry).create();

	//default add a tagecomponent
	AddComponent<TagComponent>(name == "" ? "UnKnown Name" : name);
}

Entity::Entity(entt::registry * registry, entt::entity entityUid)
{
	m_pSceneRegistry = registry;
	m_EntityUid = entityUid;
}

END_ENTERNITY

