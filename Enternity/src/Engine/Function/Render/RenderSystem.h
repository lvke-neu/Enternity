/***************************************************************************************
Author: lvke
Date:2023/2/6 22:50
Description:
RenderSystem
****************************************************************************************/
#pragma once
#include "Core/Basic/Macro.h"
#include <queue>

namespace Enternity
{
	class Scene;
	struct Vector4f;
	class RenderSystem
	{
		SINGLETON(RenderSystem);
		PRIVATE(RenderSystem);
	public:
		void initialize();
		void uninitialize();
	public:
		void setViewPort(unsigned int width, unsigned int height);
		void clear(const Vector4f& vec4);
		void drawCall(Scene* scene);
		void tick();
	private:
		void drawScene(Scene* scene);
	private:
		std::queue<Scene*> m_drawcalls;
	};
}