#pragma once

namespace Enternity
{
	class Scene;
	class FrameBuffer;
	class RenderSystem
	{
	public:
		RenderSystem();
		~RenderSystem();
	public:
		void render(Scene* scene);
		FrameBuffer* getFrameBuffer();
	private:
		bool cull(Scene* scene);
		void renderPass_Color(Scene* scene);
		void renderPass_ShadowMap();

		void onWindowResize(void* data);
	private:
		FrameBuffer* m_frameBuffer1{ nullptr };
	};

	inline FrameBuffer* RenderSystem::getFrameBuffer()
	{
		return m_frameBuffer1;
	}
}