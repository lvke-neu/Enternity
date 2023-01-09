/*
test ecs
test entt
*/

#pragma once

#include <glm/glm.hpp>
#include "Entt/entt.hpp"

class Scene
{
public:
	Scene();
	~Scene();
private:
	entt::registry m_registry;
};

struct TransformComponent
{
	TransformComponent() = default;
	TransformComponent(const glm::mat4& mat4) :
		transformMatrix(mat4)
	{

	}
	TransformComponent(const TransformComponent&) = default;
	
	glm::mat4 transformMatrix;
};