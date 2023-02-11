#include "Entity.h"
#include "Scene.h"
#include "Core/Basic/Macro.h"

namespace Enternity
{
	Entity::Entity(Scene* scene)
	{
		ENTERNITY_ASSERT(scene != nullptr);

		m_scene = scene;
		ENTERNITY_ASSERT(scene->getRegistry() != nullptr);
		m_enttId = m_scene->getRegistry()->create();
	}

	entt::entity Entity::getEnttId()
	{
		return m_enttId;
	}
}