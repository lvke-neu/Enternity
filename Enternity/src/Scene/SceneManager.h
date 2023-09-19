#pragma once

namespace Enternity
{
	class Scene;
	class SceneManager
	{
		friend class Engine;
	private:
		SceneManager();
		~SceneManager();
	public:
		Scene* getCurrentScene();
		void tick();
	private:
		Scene* m_currentScene{ nullptr };
	};

	inline Scene* SceneManager::getCurrentScene()
	{
		return m_currentScene;
	}
}