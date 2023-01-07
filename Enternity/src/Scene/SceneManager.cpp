#include "SceneManager.h"
#include "PerspectiveCamera/CameraController.h"
#include "TestDrawable/Triangle.h"

BEGIN_ENTERNITY

SceneManager::SceneManager()
{
	m_Triangle = new Triangle();
	m_CameraController = new CameraController();
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


