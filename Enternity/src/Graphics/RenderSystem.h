#pragma once

namespace Enternity
{
	class Renderer;
	class Scene;
	class FrameBuffer;
	class FrameBufferShadowMap;
	class RenderSystem
	{
	protected:
		RenderSystem();
		virtual ~RenderSystem();
	public:
		void render(Scene* scene);
		FrameBufferShadowMap* getShadowMapFrameBuffer();
		FrameBuffer* getColorFrameBuffer();
		FrameBuffer* getPostprocessFrameBuffer();
		unsigned int getTriangleCount() const;
	private:
		void shadowmapPass(Scene* scene);
		void colorPass(Scene* scene);
		void postprocessPass(Scene* scene);

		void renderModel(Scene* scene);
		void renderSkybox(Scene* scene);

		void renderModelShadowMap(Scene* scene);

		void onWindowResize(void* data);
	private:
		FrameBuffer* m_colorFrameBuffer{ nullptr };
		FrameBuffer* m_postprocessFrameBuffer{ nullptr };
		FrameBufferShadowMap* m_shadowMapFrameBuffer{ nullptr };

		Renderer* m_shadowmapShader{ nullptr };
		unsigned int m_triangleCount{ 0 };
	};

	inline FrameBufferShadowMap* RenderSystem::getShadowMapFrameBuffer()
	{
		return m_shadowMapFrameBuffer;
	}

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