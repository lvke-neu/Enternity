#pragma once
#include <entt.hpp>
#include "Engine/Log.h"

namespace Enternity
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::registry* registry);
	public:
		entt::entity getEnttID();
		bool isValidEntity();
	private:
		entt::registry* m_registry{ nullptr };
		entt::entity m_enttId{ entt::null };

	//template
	public:
		template<typename T, typename...Args>
		T& addComponent(Args&& ... args)
		{
			if (hasComponent<T>())
			{
				LOG_ERROR("Component has exist in this Entity");
				return getComponent<T>();
			}
			return  m_registry->emplace<T>(m_enttId, std::forward<Args>(args)...);
		}

		template<typename T, typename...Args>
		void removeComponent(Args&& ... args)
		{
			if (!hasComponent<T>())
			{
				LOG_ERROR("Component doesn't exist in this Entity");
				return;
			}

			m_registry->remove<T>(m_enttId);
		}

		template <typename T>
		bool hasComponent()
		{
			return m_registry->has<T>(m_enttId);
		}

		template <typename T>
		bool hasComponent() const 
		{
			return m_registry->has<T>(m_enttId);
		}

		template<typename T>
		T& getComponent() 
		{
			return m_registry->get<T>(m_enttId);
		}

		template<typename T>
		T& getComponent() const 
		{
			return m_registry->get<T>(m_enttId);
		}
	};

	inline entt::entity Entity::getEnttID()
	{
		return m_enttId;
	}


	inline bool Entity::isValidEntity()
	{
		if (!m_registry)
			return false;
		return m_registry->valid(m_enttId);
	}
}