#include "Entity.h"
#include "NameComponent.h"

namespace Enternity
{
	Entity::Entity(entt::registry* registry)
	{
		m_registry = registry;
		m_enttId = m_registry->create();
		addComponent<NameComponent>();
	}
}