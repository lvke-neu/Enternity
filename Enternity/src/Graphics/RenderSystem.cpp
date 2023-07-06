#include "RenderSystem.h"
#include "Scene/Scene.h"
#include "RHI/FrameBuffer/FrameBuffer.h"
#include "RHI/Mesh/Mesh.h"
#include "RHI/Mesh/MeshAsset.h"
#include "RHI/Mesh/VertexArray.h"
#include "RHI/Mesh/IndexBuffer.h"
#include "RHI/Renderer/Renderer.h"
#include "RHI/Renderer/RendererAsset.h"
#include "RHI/Texture/Texture.h"
#include "RHI/Texture/TextureAsset.h"
#include "Engine/Engine.h"
#include "Engine/Event/EventSystem.h"
#include "Scene/ECS/CameraComponent.h"
#include "Scene/ECS/TransformComponent.h"
#include "Scene/ECS/Visual3DComponent.h"
#include "Scene/ECS/PostprocessComponent.h"
#include "Scene/ECS/SkyboxComponent.h"
#include <glad/glad.h>

namespace Enternity
{
	//TODO: move to class Scene
	static Texture* s_defaultTexture =nullptr;
	static Renderer* s_depthRender = nullptr;
	RenderSystem::RenderSystem()
	{
		m_frameBufferColor = new FrameBuffer;
		m_frameBufferDepth = new FrameBuffer;
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::WindowResize, BIND(RenderSystem::onWindowResize));
	
		//TODO: move to class Scene
		TextureAsset ta("assets/textures/white_background.jpeg");
		ta.load(0);
		s_defaultTexture = new Texture(&ta);

		RendererAsset vsRa("assets/shaders/depth/depth.vert");
		RendererAsset psRa("assets/shaders/depth/depth.frag");
		vsRa.load(0);
		psRa.load(0);
		s_depthRender = new Renderer(&vsRa, &psRa);
	}

	RenderSystem::~RenderSystem()
	{
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::WindowResize, BIND(RenderSystem::onWindowResize));
		SAFE_DELETE_SET_NULL(m_frameBufferColor);
		SAFE_DELETE_SET_NULL(m_frameBufferDepth);
		SAFE_DELETE_SET_NULL(s_defaultTexture);
	}

	void RenderSystem::render(Scene* scene)
	{
		renderPath_Color(scene);
		renderPath_Postprocess(scene);
		renderPath_Depth(scene);
	}

	bool RenderSystem::cull(Scene* scene)
	{
		auto& cameraTransformComponent = scene->m_sceneCamera.getComponent<TransformComponent>();
		if (cameraTransformComponent.rotation.y > 54)
			return true;
		return false;
	}

	void RenderSystem::renderPath_Color(Scene* scene)
	{
		m_triangleCount = 0;
		if (scene)
		{
			m_frameBufferColor->bind();

			CHECK_GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			CHECK_GL_CALL((glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)));
			
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			auto& cameraComponent = scene->m_sceneCamera.getComponent<CameraComponent>();
			auto& cameraTransformComponent = scene->m_sceneCamera.getComponent<TransformComponent>();
			
			//skybox
			if (scene->m_skybox.getComponent<SkyboxComponent>().skyboxType != SkyboxComponent::SkyboxType::None)
			{
				auto& skyboxComponent = scene->m_skybox.getComponent<SkyboxComponent>();
				if (skyboxComponent.mesh && skyboxComponent.renderer && skyboxComponent.cubeMapTexture)
				{
					glDepthFunc(GL_LEQUAL);

					skyboxComponent.renderer->bind();
					skyboxComponent.renderer->setMat4("u_mvp", cameraComponent.getProjectionMatrix() * glm::mat4(glm::mat3(cameraTransformComponent.getInverseWorldMatrix())));
					skyboxComponent.mesh->getVertexArraies()[0]->bind();
					skyboxComponent.mesh->getIndexBuffers()[0]->bind();
					skyboxComponent.cubeMapTexture->bind(0);
					CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, skyboxComponent.mesh->getIndexBuffers()[0]->getCount(), GL_UNSIGNED_INT, (void*)0));

					skyboxComponent.renderer->unbind();
					skyboxComponent.mesh->getVertexArraies()[0]->unbind();
					skyboxComponent.mesh->getIndexBuffers()[0]->unbind();
					skyboxComponent.cubeMapTexture->unbind();

					glDepthFunc(GL_LESS);
				}
			}

			//v3d
			for (auto& entity : scene->m_entities)
			{
				if (entity.second.hasComponent<Visual3DComponent>())
				{
					auto& visual3DComponent = entity.second.getComponent<Visual3DComponent>();
					if (visual3DComponent.renderer && visual3DComponent.mesh)
					{
						const auto& vertexArraies = visual3DComponent.mesh->getVertexArraies();
						const auto& indexBuffers = visual3DComponent.mesh->getIndexBuffers();

						for (int i = 0; i < vertexArraies.size(); i++)
						{
							vertexArraies[i]->bind();
							visual3DComponent.renderer->bind();
							visual3DComponent.renderer->applyRenderPass();
							TransformComponent tc;

							visual3DComponent.renderer->setMat4("u_m", entity.second.hasComponent<TransformComponent>() ? entity.second.getComponent<TransformComponent>().getWorldMatrix() : tc.getWorldMatrix());
							visual3DComponent.renderer->setMat4("u_v", cameraTransformComponent.getInverseWorldMatrix());
							visual3DComponent.renderer->setMat4("u_p", cameraComponent.getProjectionMatrix());

							if (visual3DComponent.mesh->getTextures()[i])
							{
								visual3DComponent.mesh->getTextures()[i]->bind(0);
							}
							else
							{
								s_defaultTexture->bind(0);
							}
							
							visual3DComponent.renderer->setUint1("u_environmentMapType", (unsigned int)visual3DComponent.environmentMapType);
							if (visual3DComponent.environmentMapType != Visual3DComponent::EnvironmentMapType::None)
							{
								visual3DComponent.renderer->setVec3("u_cameraPos", cameraTransformComponent.translation);

								if (scene->m_skybox.getComponent<SkyboxComponent>().cubeMapTexture)
								{
									scene->m_skybox.getComponent<SkyboxComponent>().cubeMapTexture->bind(1);
								}
							}

							indexBuffers[i]->bind();
							CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, indexBuffers[i]->getCount(), GL_UNSIGNED_INT, (void*)0));
							m_triangleCount += indexBuffers[i]->getCount();

							if (visual3DComponent.mesh->getTextures()[i])
							{
								visual3DComponent.mesh->getTextures()[i]->unbind();
							}
							else
							{
								s_defaultTexture->unbind();
							}

							if (visual3DComponent.environmentMapType != Visual3DComponent::EnvironmentMapType::None)
							{
								if (scene->m_skybox.getComponent<SkyboxComponent>().cubeMapTexture)
								{
									scene->m_skybox.getComponent<SkyboxComponent>().cubeMapTexture->unbind();
								}
							}

							vertexArraies[i]->unbind();
							visual3DComponent.renderer->unbind();
							indexBuffers[i]->unbind();
						}

					}
				}
			}
			
			m_frameBufferColor->unbind();
		}
	}

	void RenderSystem::renderPath_Postprocess(Scene* scene)
	{
		if (scene)
		{
			m_frameBufferColor->bind();
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			auto& postprocessEntity = scene->m_scenePostprocess;
			auto& ppc = postprocessEntity.getComponent<PostprocessComponent>();
			ppc.renderer->bind();
			ppc.renderer->setUint1("u_postProcessType", (unsigned int)ppc.postprocessType);
			if (m_frameBufferColor->getTextureId() != -1)
			{
				CHECK_GL_CALL(glActiveTexture(GL_TEXTURE0 + 0));
				CHECK_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_frameBufferColor->getTextureId()));
			}
			ppc.mesh->getVertexArraies()[0]->bind();
			ppc.mesh->getIndexBuffers()[0]->bind();
			CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, ppc.mesh->getIndexBuffers()[0]->getCount(), GL_UNSIGNED_INT, (void*)0));
			ppc.renderer->unbind();
			if (m_frameBufferColor->getTextureId() != -1)
			{
				CHECK_GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
			}
			ppc.mesh->getVertexArraies()[0]->unbind();
			ppc.mesh->getIndexBuffers()[0]->unbind();

			m_frameBufferColor->unbind();
		}
	}

	void RenderSystem::renderPath_Depth(Scene* scene)
	{
		if (scene && m_bRenderPathDepth)
		{
			m_frameBufferDepth->bind();

			CHECK_GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			CHECK_GL_CALL((glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)));

			
			auto& cameraComponent = scene->m_sceneCamera.getComponent<CameraComponent>();
			auto& cameraTransformComponent = scene->m_sceneCamera.getComponent<TransformComponent>();

			for (auto& entity : scene->m_entities)
			{
				if (entity.second.hasComponent<Visual3DComponent>())
				{
					auto& visual3DComponent = entity.second.getComponent<Visual3DComponent>();
					if (s_depthRender && visual3DComponent.mesh)
					{
						const auto& vertexArraies = visual3DComponent.mesh->getVertexArraies();
						const auto& indexBuffers = visual3DComponent.mesh->getIndexBuffers();

						for (int i = 0; i < vertexArraies.size(); i++)
						{
							vertexArraies[i]->bind();
							s_depthRender->bind();
							TransformComponent tc;
							s_depthRender->setMat4("u_mvp", cameraComponent.getProjectionMatrix() * cameraTransformComponent.getInverseWorldMatrix() *
								(entity.second.hasComponent<TransformComponent>() ? entity.second.getComponent<TransformComponent>().getWorldMatrix() : tc.getWorldMatrix()));

							indexBuffers[i]->bind();
							CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, indexBuffers[i]->getCount(), GL_UNSIGNED_INT, (void*)0));

							vertexArraies[i]->unbind();
							s_depthRender->unbind();
							indexBuffers[i]->unbind();
						}
					}
				}
			}

			m_frameBufferDepth->unbind();
		}
	}	
	
	void RenderSystem::renderPath_ShadowMap(Scene* scene)
	{

	}

	void RenderSystem::onWindowResize(void* data)
	{
		WindowSize ws = *(WindowSize*)(data);
		m_frameBufferColor->resize(ws.width, ws.height);
		m_frameBufferDepth->resize(ws.width, ws.height);
	}
}