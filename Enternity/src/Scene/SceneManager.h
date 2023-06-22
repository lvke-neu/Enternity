#pragma once

namespace Enternity
{
	class Scene;
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();
	public:
		Scene* getCurrentScene();
		void onUpdateTime(float deltaTime);
	private:
		Scene* m_currentScene{ nullptr };
	};

	inline Scene* SceneManager::getCurrentScene()
	{
		return m_currentScene;
	}
}