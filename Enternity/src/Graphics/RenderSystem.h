#pragma once

namespace Enternity
{
	class Scene;
	class FrameBuffer;
	class RenderSystem
	{
	protected:
		RenderSystem();
		virtual ~RenderSystem();
	public:
		void render(Scene* scene);
		FrameBuffer* getColorFrameBuffer();
		FrameBuffer* getPostprocessFrameBuffer();
		unsigned int getTriangleCount() const;
	private:
		void color_path(Scene* scene);
		void color_path_cull(Scene* scene);
		void color_path_skyboxPass(Scene* scene);
		void color_path_shadowmapPass(Scene* scene);
		void color_path_visual3dPass(Scene* scene);
		void color_path_particlePass(Scene* scene);

		void postprocess_path(Scene* scene);

		void onWindowResize(void* data);
	private:
		FrameBuffer* m_colorFrameBuffer{ nullptr };
		FrameBuffer* m_postprocessFrameBuffer{ nullptr };
		unsigned int m_triangleCount{ 0 };
	};

	inline FrameBuffer* RenderSystem::getColorFrameBuffer()
	{
		return m_colorFrameBuffer;
	}

	inline FrameBuffer* RenderSystem::getPostprocessFrameBuffer()
	{
		return m_postprocessFrameBuffer;
	}

	inline unsigned int RenderSystem::getTriangleCount() const
	{
		return m_triangleCount;
	}
}