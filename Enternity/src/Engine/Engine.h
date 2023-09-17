#pragma once
#include "Common/Macro.h"

namespace Enternity
{
	class Timer;
	class RenderView;
	class EventSystem;
	class BlobLoaderManager;
	class NativeFileSystem;
	class AssetLoader;
	class GraphicsSystem;
	class SceneManager;
	class UiRender;
	class Engine
	{
		SINGLETON(Engine);
		PRIVATE(Engine);
	public:
		void initialize();
		void uninitialize();
		void run();
		Timer* getTimer();
	public:
		GraphicsSystem* getGraphicsSystem();
		EventSystem* getEventSystem();
		SceneManager* getSceneManager();
		RenderView* getRenderView();
		BlobLoaderManager* getBlobLoaderManager();
		NativeFileSystem* getNativeFileSystem();
		AssetLoader* getAssetLoader();
	private:
		GraphicsSystem* m_graphicsSystem{ nullptr };
		EventSystem* m_eventSystem{ nullptr };
		RenderView* m_renderView{ nullptr };
		SceneManager* m_sceneManager{ nullptr };
		BlobLoaderManager* m_blobLoaderManager{ nullptr };
		NativeFileSystem* m_nativeFileSystem{ nullptr };
		Timer* m_timer{ nullptr };
		AssetLoader* m_assetLoader{ nullptr };
		UiRender* m_uiRender{ nullptr };
	};

	inline GraphicsSystem* Engine::getGraphicsSystem()
	{
		return m_graphicsSystem;
	}

	inline EventSystem* Engine::getEventSystem()
	{
		return m_eventSystem;
	}

	inline SceneManager* Engine::getSceneManager()
	{
		return m_sceneManager;
	}

	inline BlobLoaderManager* Engine::getBlobLoaderManager()
	{
		return m_blobLoaderManager;
	}

	inline RenderView* Engine::getRenderView()
	{
		return m_renderView;
	}

	inline Timer* Engine::getTimer()
	{
		return m_timer;
	}

	inline NativeFileSystem* Engine::getNativeFileSystem()
	{
		return m_nativeFileSystem;
	}

	inline AssetLoader* Engine::getAssetLoader()
	{
		return m_assetLoader;
	}
}