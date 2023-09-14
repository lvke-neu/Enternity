#include "RenderSystem.h"
#include "Scene/Scene.h"
#include "RHI/FrameBuffer/FrameBuffer.h"
#include "Engine/Engine.h"
#include "Engine/Timer.h"
#include "Engine/EventSystem.h"
#include "Engine/RenderView.h"
#include "Engine/AssetLoader.h"
#include "Engine/BlobLoaderManager.h"
#include "Scene/ECS/CameraComponent.h"
#include "Scene/ECS/TransformComponent.h"
#include "Scene/ECS/PostProcessComponent.h"
#include "Scene/ECS/SkyBoxComponent.h"
#include "Scene/ECS/Visual3DComponent.h"
#include "Scene/ECS/SkeletonModelComponent.h"
#include "Scene/ECS/StaticModelComponent.h"
#include "Scene/ECS/ModelComponent.h"
#include "Scene/ECS/PBRMaterialComponent.h"
#include "Scene/ECS/SunLightComponent.h"
#include "Scene/Model/Model.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Graphics/RHI/Renderer/RendererBlobLoader.h"
#include "Graphics/RHI/Texture/TextureBlobLoader.h"
#include "Graphics/RHI/Mesh/MeshBlobLoader.h"
#include <glad/glad.h>

namespace Enternity
{
	const unsigned int SHADOW_MAP_WIDTH = 4096;
	const unsigned int SHADOW_MAP_HEIGHT = 4096;
	const float ORTHO_LENGTH = 50.0f;

	RenderSystem::RenderSystem()
	{
		Engine::GetInstance().getBlobLoaderManager()->registerBlobLoader(new RendererBlobLoader);
		Engine::GetInstance().getBlobLoaderManager()->registerBlobLoader(new TextureBlobLoader);
		Engine::GetInstance().getBlobLoaderManager()->registerBlobLoader(new MeshBlobLoader);

		m_shadowMapFrameBuffer = new FrameBufferShadowMap(SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT);
		m_colorFrameBuffer = new FrameBuffer(100, 100, { ColorAttachmentFormat::RGBA8, ColorAttachmentFormat::RGB8, ColorAttachmentFormat::RED_INTEGER });
		m_postprocessFrameBuffer = new FrameBuffer(100, 100, { ColorAttachmentFormat::RGBA8 });
		m_shadowmapRenderer = dynamic_cast<Renderer*>(Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/shadowmap/shadowmap.rdr"));
		m_shadowmapRenderer2 = dynamic_cast<Renderer*>(Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/shadowmap/shadowmap2.rdr"));

		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::WindowResize, BIND(RenderSystem::onWindowResize));
	}

	RenderSystem::~RenderSystem()
	{
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::WindowResize, BIND(RenderSystem::onWindowResize));
		SAFE_DELETE_SET_NULL(m_shadowMapFrameBuffer);
		SAFE_DELETE_SET_NULL(m_colorFrameBuffer);
		SAFE_DELETE_SET_NULL(m_postprocessFrameBuffer);	
		SAFE_DELETE_SET_NULL(m_shadowmapRenderer);
		SAFE_DELETE_SET_NULL(m_shadowmapRenderer2);
	}

	void RenderSystem::render(Scene* scene)
	{
		shadowmapPass(scene);
		colorPass(scene);
		postprocessPass(scene);
	}

	void RenderSystem::shadowmapPass(Scene* scene)
	{
		glViewport(0, 0, SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT);
		m_shadowMapFrameBuffer->bind();
		glClear(GL_DEPTH_BUFFER_BIT);

		renderModelShadowMap(scene);

		glViewport(0, 0, Engine::GetInstance().getRenderView()->getWidth(), Engine::GetInstance().getRenderView()->getHeight());
		m_shadowMapFrameBuffer->unbind();
	}

	void RenderSystem::renderModelShadowMap(Scene* scene)
	{
		//for (auto& entity : scene->m_entities)
		//{
		//	if (entity.second.hasComponent<StaticModelComponent>())
		//	{
		//		auto& staticModelComponent = entity.second.getComponent<StaticModelComponent>();

		//		if (m_shadowmapRenderer && m_shadowmapRenderer->isLoadSucceeded() &&
		//			staticModelComponent.model && staticModelComponent.model->isLoadSucceeded())
		//		{
		//			m_shadowmapRenderer->bind();

		//			glm::mat4 model = entity.second.hasComponent<TransformComponent>() ? entity.second.getComponent<TransformComponent>().getWorldMatrix() : glm::mat4(1);
		//			glm::mat4 view = glm::lookAt(-scene->m_sceneSunlight.getComponent<SunLightComponent>().direction, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//			glm::mat4 proj = glm::ortho(-ORTHO_LENGTH, ORTHO_LENGTH, -ORTHO_LENGTH, ORTHO_LENGTH, 1.0f, 100.0f);

		//			m_shadowmapRenderer->setMat4("u_m", model);
		//			m_shadowmapRenderer->setMat4("u_v", view);
		//			m_shadowmapRenderer->setMat4("u_p", proj);

		//			staticModelComponent.model->draw();
		//			m_shadowmapRenderer->unbind();
		//		}
		//	}
		//}
	}

	void RenderSystem::colorPass(Scene* scene)
	{
		/*if (scene)
		{
			m_colorFrameBuffer->bind();

			CHECK_GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			CHECK_GL_CALL((glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)));

			renderModel(scene);
			renderSkybox(scene);
			
			m_colorFrameBuffer->unbind();
		}*/
	}

	void RenderSystem::renderModel(Scene* scene)
	{
		//for (auto& entity : scene->m_entities)
		//{
		//	if (entity.second.hasComponent<ModelComponent>())
		//	{
		//		auto& modelComponent = entity.second.getComponent<ModelComponent>();

		//		if (modelComponent.model && modelComponent.model->isLoadSucceeded() &&
		//			modelComponent.renderer && modelComponent.renderer->isLoadSucceeded())
		//		{
		//			modelComponent.renderer->bind();

		//			glm::mat4 model = entity.second.hasComponent<TransformComponent>() ? entity.second.getComponent<TransformComponent>().getWorldMatrix() : glm::mat4(1);
		//			glm::mat4 view = scene->m_sceneCamera.getComponent<TransformComponent>().getInverseWorldMatrix();
		//			glm::mat4 proj = scene->m_sceneCamera.getComponent<CameraComponent>().getProjectionMatrix();

		//			modelComponent.renderer->setMat4("u_m", model);
		//			modelComponent.renderer->setMat4("u_v", view);
		//			modelComponent.renderer->setMat4("u_p", proj);

		//			modelComponent.model->draw(modelComponent.renderer);

		//			modelComponent.renderer->unbind();
		//		}
		//	}
		//}
	}

	void RenderSystem::renderSkybox(Scene* scene)
	{
		/*auto& skyBoxComponent = scene->m_sceneSkybox.getComponent<SkyBoxComponent>();
		if (skyBoxComponent.renderer && skyBoxComponent.mesh && skyBoxComponent.textureCubeMapHDR && 
			skyBoxComponent.renderer->isLoadSucceeded() && skyBoxComponent.mesh->isLoadSucceeded() && skyBoxComponent.textureCubeMapHDR->isLoadSucceeded())
		{
			glDepthFunc(GL_LEQUAL);
			skyBoxComponent.renderer->bind();
			skyBoxComponent.textureCubeMapHDR->bind(0);

			glm::mat4 view = scene->m_sceneCamera.getComponent<TransformComponent>().getInverseWorldMatrix();
			glm::mat4 proj = scene->m_sceneCamera.getComponent<CameraComponent>().getProjectionMatrix();

			skyBoxComponent.renderer->setMat4("u_mvp", proj * glm::mat4(glm::mat3(view)));
			skyBoxComponent.mesh->draw();

			skyBoxComponent.textureCubeMapHDR->unbind();
			skyBoxComponent.renderer->unbind();

			glDepthFunc(GL_LESS);
		}*/
	}

	void RenderSystem::postprocessPass(Scene* scene)
	{
		/*m_postprocessFrameBuffer->bind();

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		auto& postprocessEntity = scene->m_scenePostprocess;
		auto& ppc = postprocessEntity.getComponent<PostProcessComponent>();
		if (ppc.renderer && ppc.mesh)
		{
			ppc.renderer->bind();
			ppc.renderer->setUint1("u_postProcessType", ppc.postprocessType);
			Texture2D::Bind(m_colorFrameBuffer->getTextureId(0), 0);
			ppc.mesh->draw();
			Texture2D::UnBind(0);
			ppc.renderer->unbind();
		}

		m_postprocessFrameBuffer->unbind();*/
	}

	void RenderSystem::onWindowResize(void* data)
	{
		WindowSize ws = *(WindowSize*)(data);
		m_colorFrameBuffer->resize(ws.width, ws.height);
		m_postprocessFrameBuffer->resize(ws.width, ws.height);
	}
}