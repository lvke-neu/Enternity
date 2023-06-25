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
		FrameBuffer* getColorFrameBuffer();
		FrameBuffer* getDepthFrameBuffer();
	private:
		bool cull(Scene* scene);
		void renderPath_Color(Scene* scene);
		void renderPath_Depth(Scene* scene);
		void renderPath_ShadowMap(Scene* scene);

		void onWindowResize(void* data);
	private:
		FrameBuffer* m_frameBufferColor{ nullptr };
		FrameBuffer* m_frameBufferDepth{ nullptr };
	};

	inline FrameBuffer* RenderSystem::getColorFrameBuffer()
	{
		return m_frameBufferColor;
	}

	inline FrameBuffer* RenderSystem::getDepthFrameBuffer()
	{
		return m_frameBufferDepth;
	}
}