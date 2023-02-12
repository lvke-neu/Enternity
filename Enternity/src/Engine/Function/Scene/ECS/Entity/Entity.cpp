#include "Entity.h"
#include "Core/Basic/UUID.h"


namespace Enternity
{
	Entity::Entity(entt::registry* registry)
	{
		ENTERNITY_ASSERT(registry != nullptr);

		m_registry = registry;
		m_enttId = m_registry->create();
		m_uuid = UUID::Generate();
	}

	entt::entity Entity::getEnttId()
	{
		return m_enttId;
	}

	std::string Entity::getUUID()
	{
		return m_uuid;
	}
}