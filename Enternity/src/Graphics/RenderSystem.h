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
		void render_path_1(Scene* scene);
		void render_path_2();

		void onWindowResize(void* data);
	private:
		FrameBuffer* m_frameBuffer1{ nullptr };
	};

	inline FrameBuffer* RenderSystem::getFrameBuffer()
	{
		return m_frameBuffer1;
	}
}