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
		unsigned int getTriangleCount() const;
	private:
		void cull(Scene* scene);
		void skyboxPass(Scene* scene);
		void shadowmapPass(Scene* scene);
		void visual3dPass(Scene* scene);
		void postprocessPass(Scene* scene);

		void onWindowResize(void* data);
	private:
		FrameBuffer* m_frameBufferColor{ nullptr };
		unsigned int m_triangleCount{ 0 };
	};

	inline FrameBuffer* RenderSystem::getColorFrameBuffer()
	{
		return m_frameBufferColor;
	}

	inline unsigned int RenderSystem::getTriangleCount() const
	{
		return m_triangleCount;
	}
}