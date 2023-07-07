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

		unsigned int getTriangleCount() const;
		bool* getIsRenderPathDepth();
	private:
		void cull(Scene* scene);
		void skyboxPass(Scene* scene);
		void shadowmapPass(Scene* scene);
		void visual3dPass(Scene* scene);
		void postprocessPass(Scene* scene);

		void onWindowResize(void* data);
	private:
		FrameBuffer* m_frameBufferColor{ nullptr };
		FrameBuffer* m_frameBufferDepth{ nullptr };
		unsigned int m_triangleCount{ 0 };
		bool m_bRenderPathDepth{ false };
	};

	inline FrameBuffer* RenderSystem::getColorFrameBuffer()
	{
		return m_frameBufferColor;
	}

	inline FrameBuffer* RenderSystem::getDepthFrameBuffer()
	{
		return m_frameBufferDepth;
	}

	inline unsigned int RenderSystem::getTriangleCount() const
	{
		return m_triangleCount;
	}

	inline bool* RenderSystem::getIsRenderPathDepth() 
	{
		return &m_bRenderPathDepth;
	}
}