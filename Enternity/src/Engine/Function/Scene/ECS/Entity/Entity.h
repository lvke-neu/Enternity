/***************************************************************************************
Author: lvke
Date:2023/2/11 14:09
Description:
Entity
****************************************************************************************/
#pragma once
#include <entt.hpp>
#include <string>
#include "Core/Log/Log.h"
#include "Core/Basic/Macro.h"

namespace Enternity
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::registry* registry);
		~Entity() = default;
		Entity(const Entity&) = default;
		Entity& operator=(const Entity&) = default;
	public:
		entt::entity getEnttId();
		std::string getUUID();
	private:
		entt::registry* m_registry{ nullptr };
		entt::entity m_enttId{ entt::null };
		std::string m_uuid{ "" };

	//template
	public:
		template<typename T, typename...Args>
		T& addComponent(Args&& ... args)
		{
			ENTERNITY_ASSERT(m_registry != nullptr);
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
			ENTERNITY_ASSERT(m_registry != nullptr);
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
			ENTERNITY_ASSERT(m_registry != nullptr);
			return m_registry->has<T>(m_enttId);
		}

		template<typename T>
		T& getComponent() const
		{
			ENTERNITY_ASSERT(m_registry != nullptr);
			return m_registry->get()<T>(m_enttId);
		}
	};
}