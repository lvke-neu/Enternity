#include "SceneManager.h"
#include "PerspectiveCamera/CameraController.h"
#include "TestDrawable/Triangle.h"
#include "ECS/Entity/Entity.h"

BEGIN_ENTERNITY

class BB
{

};
struct aaaa
{
	float a;
	aaaa(int x, const BB& bb)
	{
		a = x;
	}
};

struct bbbb
{
	float b;
};

entt::registry SceneManager::s_Registry;

SceneManager::SceneManager()
{
	m_Triangle = new Triangle();
	m_CameraController = new CameraController();

	Entity entity;
	bool a  = entity.HasComponent<aaaa>();
	entity.AddComponent<aaaa>(5, BB());
	a = entity.HasComponent<aaaa>();
	
	if (a == true)
	{
		auto& comp = entity.GetComponent<aaaa>();
		int i = 0;
		i++;
	}
	
	entity.RemoveComponent<aaaa>();
	a = entity.HasComponent<aaaa>();

	Entity entity2("entity2");


	int i = 0;
	i++;
}

SceneManager::~SceneManager()
{
	SAFE_DELETE_SET_NULL(m_Triangle);
	SAFE_DELETE_SET_NULL(m_CameraController);
}

void SceneManager::Tick(float deltaTime)
{
	m_Triangle->draw();
}

END_ENTERNITY


