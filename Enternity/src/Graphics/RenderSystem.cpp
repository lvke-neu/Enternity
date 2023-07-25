#include "RenderSystem.h"
#include "Scene/Scene.h"
#include "RHI/FrameBuffer/FrameBuffer.h"
#include "Engine/Engine.h"
#include "Engine/Timer.h"
#include "Engine/EventSystem.h"
#include "Scene/ECS/CameraComponent.h"
#include "Scene/ECS/TransformComponent.h"
#include "Scene/ECS/PostProcessComponent.h"
#include <glad/glad.h>

namespace Enternity
{
	RenderSystem::RenderSystem()
	{
		m_colorFrameBuffer = new FrameBuffer(100, 100, {ColorAttachmentFormat::RGBA8, ColorAttachmentFormat::RGB8, ColorAttachmentFormat::RED_INTEGER });
		m_postprocessFrameBuffer = new FrameBuffer(100, 100, { ColorAttachmentFormat::RGBA8 });
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::WindowResize, BIND(RenderSystem::onWindowResize));
	}

	RenderSystem::~RenderSystem()
	{
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::WindowResize, BIND(RenderSystem::onWindowResize));
		SAFE_DELETE_SET_NULL(m_colorFrameBuffer);
		SAFE_DELETE_SET_NULL(m_postprocessFrameBuffer);
	}

	void RenderSystem::render(Scene* scene)
	{
		color_path(scene);
		postprocess_path(scene);
	}

	void RenderSystem::color_path(Scene* scene)
	{
		if (scene)
		{
			m_colorFrameBuffer->bind();

			CHECK_GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			CHECK_GL_CALL((glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)));
			
			color_path_cull(scene);
			color_path_skyboxPass(scene);
			color_path_shadowmapPass(scene);
			color_path_visual3dPass(scene);
			color_path_particlePass(scene);

			m_colorFrameBuffer->unbind();
		}
	}

	void RenderSystem::color_path_cull(Scene* scene)
	{
		
	}

	void RenderSystem::color_path_skyboxPass(Scene* scene)
	{
		//auto& cameraComponent = scene->m_sceneCamera.getComponent<CameraComponent>();
		//auto& cameraTransformComponent = scene->m_sceneCamera.getComponent<TransformComponent>();

		//if (scene->m_skybox.getComponent<SkyboxComponent>().skyboxType != SkyboxComponent::SkyboxType::None)
		//{
		//	auto& skyboxComponent = scene->m_skybox.getComponent<SkyboxComponent>();
		//	if (skyboxComponent.mesh && skyboxComponent.renderer && skyboxComponent.cubeMapTexture)
		//	{
		//		glDepthFunc(GL_LEQUAL);

		//		skyboxComponent.renderer->bind();
		//		skyboxComponent.renderer->setMat4("u_mvp", cameraComponent.getProjectionMatrix() * glm::mat4(glm::mat3(cameraTransformComponent.getInverseWorldMatrix())));
		//		skyboxComponent.renderer->setInt1("u_entityId", -1);
		//		skyboxComponent.mesh->getVertexArraies()[0]->bind();
		//		skyboxComponent.mesh->getIndexBuffers()[0]->bind();
		//		skyboxComponent.cubeMapTexture->bind(0);
		//		CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, skyboxComponent.mesh->getIndexBuffers()[0]->getCount(), GL_UNSIGNED_INT, (void*)0));

		//		skyboxComponent.renderer->unbind();
		//		skyboxComponent.mesh->getVertexArraies()[0]->unbind();
		//		skyboxComponent.mesh->getIndexBuffers()[0]->unbind();
		//		skyboxComponent.cubeMapTexture->unbind();

		//		glDepthFunc(GL_LESS);
		//	}
		//}
	}

	void RenderSystem::color_path_shadowmapPass(Scene* scene)
	{

	}

	void RenderSystem::color_path_visual3dPass(Scene* scene)
	{
		//m_triangleCount = 0;

		//auto& cameraComponent = scene->m_sceneCamera.getComponent<CameraComponent>();
		//auto& cameraTransformComponent = scene->m_sceneCamera.getComponent<TransformComponent>();

		////opaque
		//std::map<float, Entity> blendEntities;
		//for (auto& entity : scene->m_entities)
		//{
		//	if (entity.second.hasComponent<Visual3DComponent>())
		//	{
		//		auto& visual3DComponent = entity.second.getComponent<Visual3DComponent>();
		//		if (visual3DComponent.renderer && visual3DComponent.mesh)
		//		{
		//			visual3DComponent.renderer->bind();
		//			if (visual3DComponent.renderer->getRenderPass().enableBlend)
		//			{
		//				float distance = glm::length(cameraTransformComponent.translation - 
		//					(entity.second.hasComponent<TransformComponent>() ? 
		//						entity.second.getComponent<TransformComponent>().translation : glm::vec3(0.0f)));
		//				blendEntities[distance] = entity.second;
		//				continue;
		//			}
		//			visual3DComponent.renderer->applyRenderPass();
		//			visual3DComponent.renderer->setMat4("u_m", entity.second.hasComponent<TransformComponent>() ? entity.second.getComponent<TransformComponent>().getWorldMatrix() : glm::mat4(1.0f));
		//			visual3DComponent.renderer->setMat4("u_v", cameraTransformComponent.getInverseWorldMatrix());
		//			visual3DComponent.renderer->setMat4("u_p", cameraComponent.getProjectionMatrix());
		//			visual3DComponent.renderer->setUint1("u_environmentMapType", (unsigned int)visual3DComponent.environmentMapType);
		//			visual3DComponent.renderer->setInt1("u_entityId", (int)entity.first);
		//			if (visual3DComponent.environmentMapType != Visual3DComponent::EnvironmentMapType::None)
		//			{
		//				visual3DComponent.renderer->setVec3("u_cameraPos", cameraTransformComponent.translation);

		//				if (scene->m_skybox.getComponent<SkyboxComponent>().cubeMapTexture)
		//				{
		//					scene->m_skybox.getComponent<SkyboxComponent>().cubeMapTexture->bind(1);
		//				}
		//			}

		//			const auto& vertexArraies = visual3DComponent.mesh->getVertexArraies();
		//			const auto& indexBuffers = visual3DComponent.mesh->getIndexBuffers();
		//			const auto& textures = visual3DComponent.mesh->getTextures();
		//			for (int i = 0; i < vertexArraies.size(); i++)
		//			{
		//				vertexArraies[i]->bind();

		//				if (textures[i])
		//				{
		//					textures[i]->bind(0);
		//				}

		//				indexBuffers[i]->bind();
		//				CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, indexBuffers[i]->getCount(), GL_UNSIGNED_INT, (void*)0));
		//				m_triangleCount += indexBuffers[i]->getCount();

		//				if (textures[i])
		//				{
		//					textures[i]->unbind();
		//				}

		//				if (visual3DComponent.environmentMapType != Visual3DComponent::EnvironmentMapType::None)
		//				{
		//					if (scene->m_skybox.getComponent<SkyboxComponent>().cubeMapTexture)
		//					{
		//						scene->m_skybox.getComponent<SkyboxComponent>().cubeMapTexture->unbind();
		//					}
		//				}

		//				vertexArraies[i]->unbind();
		//				indexBuffers[i]->unbind();
		//			}

		//			visual3DComponent.renderer->unbind();
		//		}
		//	}
		//}

		////transparent
		//for (auto it = blendEntities.rbegin(); it != blendEntities.rend(); ++it)
		//{
		//	if (it->second.hasComponent<Visual3DComponent>())
		//	{
		//		auto& visual3DComponent = it->second.getComponent<Visual3DComponent>();
		//		if (visual3DComponent.renderer && visual3DComponent.mesh)
		//		{
		//			visual3DComponent.renderer->bind();
		//			visual3DComponent.renderer->applyRenderPass();
		//			visual3DComponent.renderer->setMat4("u_m", it->second.hasComponent<TransformComponent>() ? it->second.getComponent<TransformComponent>().getWorldMatrix() : glm::mat4(1.0f));
		//			visual3DComponent.renderer->setMat4("u_v", cameraTransformComponent.getInverseWorldMatrix());
		//			visual3DComponent.renderer->setMat4("u_p", cameraComponent.getProjectionMatrix());
		//			visual3DComponent.renderer->setUint1("u_environmentMapType", (unsigned int)visual3DComponent.environmentMapType);
		//			visual3DComponent.renderer->setInt1("u_entityId", (int)it->first);
		//			if (visual3DComponent.environmentMapType != Visual3DComponent::EnvironmentMapType::None)
		//			{
		//				visual3DComponent.renderer->setVec3("u_cameraPos", cameraTransformComponent.translation);

		//				if (scene->m_skybox.getComponent<SkyboxComponent>().cubeMapTexture)
		//				{
		//					scene->m_skybox.getComponent<SkyboxComponent>().cubeMapTexture->bind(1);
		//				}
		//			}

		//			const auto& vertexArraies = visual3DComponent.mesh->getVertexArraies();
		//			const auto& indexBuffers = visual3DComponent.mesh->getIndexBuffers();
		//			const auto& textures = visual3DComponent.mesh->getTextures();
		//			for (int i = 0; i < vertexArraies.size(); i++)
		//			{
		//				vertexArraies[i]->bind();

		//				if (textures[i])
		//				{
		//					textures[i]->bind(0);
		//				}

		//				indexBuffers[i]->bind();
		//				CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, indexBuffers[i]->getCount(), GL_UNSIGNED_INT, (void*)0));
		//				m_triangleCount += indexBuffers[i]->getCount();

		//				if (textures[i])
		//				{
		//					textures[i]->unbind();
		//				}

		//				if (visual3DComponent.environmentMapType != Visual3DComponent::EnvironmentMapType::None)
		//				{
		//					if (scene->m_skybox.getComponent<SkyboxComponent>().cubeMapTexture)
		//					{
		//						scene->m_skybox.getComponent<SkyboxComponent>().cubeMapTexture->unbind();
		//					}
		//				}

		//				vertexArraies[i]->unbind();
		//				indexBuffers[i]->unbind();
		//			}

		//			visual3DComponent.renderer->unbind();
		//		}
		//	}
		//}
	}

	void RenderSystem::color_path_particlePass(Scene* scene)
	{
		//auto& cameraComponent = scene->m_sceneCamera.getComponent<CameraComponent>();
		//auto& cameraTransformComponent = scene->m_sceneCamera.getComponent<TransformComponent>();

		//for (auto& entity : scene->m_entities)
		//{
		//	if (entity.second.hasComponent<ParticleComponent>())
		//	{
		//		auto& particleComponent = entity.second.getComponent<ParticleComponent>();
		//		if (particleComponent.renderer && particleComponent.mesh && particleComponent.texture)
		//		{
		//			particleComponent.renderer->bind();
		//			particleComponent.renderer->applyRenderPass();

		//			glm::mat4 m{ 1.0f }; 
		//			if (entity.second.hasComponent<TransformComponent>())
		//			{
		//				auto& transformComponent = entity.second.getComponent<TransformComponent>();
		//				static glm::vec3 rotation{ 0.0,0.0,0.0 };
		//				rotation.y = std::sin(Engine::GetInstance().getTimer()->totalTime() * 0.0005f);
		//				transformComponent.translation = transformComponent.translation * glm::mat3(glm::mat4_cast(glm::qua<float>(rotation)));
		//				m = entity.second.getComponent<TransformComponent>().getWorldMatrix();
		//			}

		//			particleComponent.renderer->setMat4("u_mvp", cameraComponent.getProjectionMatrix() * cameraTransformComponent.getInverseWorldMatrix() * m);
		//			particleComponent.texture->bind(0);

		//			const auto& vertexArraies = particleComponent.mesh->getVertexArraies();
		//			const auto& indexBuffers = particleComponent.mesh->getIndexBuffers();
		//			const auto& textures = particleComponent.mesh->getTextures();
		//			for (int i = 0; i < vertexArraies.size(); i++)
		//			{
		//				vertexArraies[i]->bind();

		//				indexBuffers[i]->bind();
		//				CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, indexBuffers[i]->getCount(), GL_UNSIGNED_INT, (void*)0));
		//				m_triangleCount += indexBuffers[i]->getCount();

		//				vertexArraies[i]->unbind();
		//				indexBuffers[i]->unbind();
		//			}

		//			particleComponent.texture->unbind();
		//			particleComponent.renderer->unbind();
		//		}
		//	}
		//}
	}

	void RenderSystem::postprocess_path(Scene* scene)
	{
		m_postprocessFrameBuffer->bind();

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		auto& postprocessEntity = scene->m_scenePostprocess;
		auto& ppc = postprocessEntity.getComponent<PostProcessComponent>();
		ppc.draw(m_colorFrameBuffer->getTextureId(0));

		m_postprocessFrameBuffer->unbind();
	}

	void RenderSystem::onWindowResize(void* data)
	{
		WindowSize ws = *(WindowSize*)(data);
		m_colorFrameBuffer->resize(ws.width, ws.height);
		m_postprocessFrameBuffer->resize(ws.width, ws.height);
	}
}